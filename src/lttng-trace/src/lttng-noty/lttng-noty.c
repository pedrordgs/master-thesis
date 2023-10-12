#include "lttng-noty.h"

static void track_pid(const char *session_name, pid_t pid) {
  struct lttng_process_attr_tracker_handle *tracker_handle;
  int status = lttng_session_get_tracker_handle(session_name, LTTNG_DOMAIN_KERNEL, LTTNG_PROCESS_ATTR_PROCESS_ID,
                                                &tracker_handle);
  if (status != LTTNG_OK) {
    printf("[ERROR - lttng-noty] Failed to get tracker handle for pid %d: %s\n", pid, lttng_strerror(-status));
    return;
  }
  status = lttng_process_attr_tracker_handle_set_tracking_policy(tracker_handle, LTTNG_TRACKING_POLICY_INCLUDE_SET);
  if (status != LTTNG_PROCESS_ATTR_TRACKER_HANDLE_STATUS_OK) {
    printf("[ERROR - lttng-noty] Failed to set tracking policy: %d\n", status);
  }
  status = lttng_process_attr_process_id_tracker_handle_add_pid(tracker_handle, pid);
  if (status != LTTNG_PROCESS_ATTR_TRACKER_HANDLE_STATUS_OK) {
    printf("[ERROR - lttng-noty] Failed to add pid to tracker %d: %d\n", pid, status);
  } else {
    printf("[INFO - lttng-noty] Added pid %d to tracker for %s\n", pid, session_name);
  }
  lttng_process_attr_tracker_handle_destroy(tracker_handle);
}

static bool subscribe_fork_triggers(struct lttng_notification_channel *notification_channel) {
  int found = 0;

  struct lttng_triggers *triggers = NULL;
  int status = lttng_list_triggers(&triggers);
  if (status != LTTNG_OK) {
    printf("[ERROR - lttng-noty] Failed to list triggers: %s\n", lttng_strerror(-status));
  }

  unsigned int trigger_count;
  status = lttng_triggers_get_count(triggers, &trigger_count);
  if (status != LTTNG_TRIGGER_STATUS_OK) {
    printf("[ERROR - lttng-noty] Failed to get triggers count: %d\n", status);
  }

  for (unsigned int i = 0; i < trigger_count && !found; i++) {
    const struct lttng_trigger *trigger = lttng_triggers_get_at_index(triggers, i);
    const char *trigger_name;
    status = lttng_trigger_get_name(trigger, &trigger_name);
    if (status != LTTNG_TRIGGER_STATUS_OK) {
      printf("[ERROR - lttng-noty] Failed to get trigger name: %d\n", status);
    }

    if (strcmp(trigger_name, PROCESS_FORK_TRIGGER_NAME) == 0) {
      status = lttng_notification_channel_subscribe(notification_channel, lttng_trigger_get_const_condition(trigger));
      if (status != LTTNG_NOTIFICATION_CHANNEL_STATUS_OK) {
        printf("[ERROR - lttng-noty] Failed to subscribe trigger %s: %d\n", trigger_name, status);
      } else {
        printf("[INFO - lttng-noty] Subscribed trigger %s\n", trigger_name);
      }
      found = 1;
    }
  }

  lttng_triggers_destroy(triggers);

  return found;
}

static gboolean equal_pid_func(gconstpointer a, gconstpointer b) {
  const pid_t *pid_a = a;
  const pid_t *pid_b = b;
  return *pid_a - *pid_b;
}

static pid_t parse_pid_from_field_value(const struct lttng_event_field_value *pid_field_value) {
  pid_t ret;
  int status;
  uint64_t uaux;
  int64_t aux;
  switch (lttng_event_field_value_get_type(pid_field_value)) {
  case LTTNG_EVENT_FIELD_VALUE_TYPE_UNSIGNED_INT:
    status = lttng_event_field_value_unsigned_int_get_value(pid_field_value, &uaux);
    if (status != LTTNG_EVENT_FIELD_VALUE_STATUS_OK) {
      printf("[ERROR - lttng-noty] Failed to get pid from field value: %d\n", status);
      return -1;
    }
    ret = (pid_t)uaux;
    break;
  case LTTNG_EVENT_FIELD_VALUE_TYPE_SIGNED_INT:
    status = lttng_event_field_value_signed_int_get_value(pid_field_value, &aux);
    if (status != LTTNG_EVENT_FIELD_VALUE_STATUS_OK) {
      printf("[ERROR - lttng-noty] Failed to get pid from field value: %d\n", status);
      return -1;
    }
    ret = (pid_t)aux;
    break;
  default:
    ret = -1;
    break;
  }

  return ret;
}

static void handle_notification(struct lttng_notification *notification, char *session_name, GArray *allowed_pids) {
  const struct lttng_trigger *trigger = lttng_notification_get_trigger(notification);
  const char *trigger_name;
  int status = lttng_trigger_get_name(trigger, &trigger_name);
  if (status != LTTNG_TRIGGER_STATUS_OK) {
    printf("[ERROR - lttng-noty] Failed to get trigger name: %d\n", status);
    return;
  }

  if (strcmp(trigger_name, PROCESS_FORK_TRIGGER_NAME) != 0) {
    printf("[WARNING - lttng-noty] Received an unexpected trigger %s\n", trigger_name);
  }

  const struct lttng_evaluation *evaluation = lttng_notification_get_evaluation(notification);
  const struct lttng_event_field_value *field_values;
  status = lttng_evaluation_event_rule_matches_get_captured_values(evaluation, &field_values);
  if (status != LTTNG_EVALUATION_EVENT_RULE_MATCHES_STATUS_OK) {
    printf("[ERROR - lttng-noty] Failed to get event-rule-matches captured values: %d\n", status);
    return;
  }

  const struct lttng_event_field_value *pid_field_value;
  status = lttng_event_field_value_array_get_element_at_index(field_values, 0, &pid_field_value);
  if (status != LTTNG_EVENT_FIELD_VALUE_STATUS_OK) {
    printf("[ERROR - lttng-noty] Failed to get index 0 from field value array: %d\n", status);
    return;
  }

  pid_t pid = parse_pid_from_field_value(pid_field_value);
  if (pid == -1) {
    printf("[ERROR - lttng-noty] Failed to parse pid from field value\n");
    return;
  }

  uint pid_index;
  if (g_array_binary_search(allowed_pids, &pid, (GEqualFunc)equal_pid_func, &pid_index)) {
    if (strcmp(trigger_name, PROCESS_FORK_TRIGGER_NAME) == 0) {
      const struct lttng_event_field_value *child_pid_field_value;
      status = lttng_event_field_value_array_get_element_at_index(field_values, 1, &child_pid_field_value);
      if (status != LTTNG_EVENT_FIELD_VALUE_STATUS_OK) {
        printf("[ERROR - lttng-noty] Failed to get index 1 from field value array: %d\n", status);
        return;
      }
      pid_t child_pid = parse_pid_from_field_value(child_pid_field_value);
      if (child_pid == -1) {
        printf("[ERROR - lttng-noty] Failed to parse child pid from field value\n");
        return;
      }

      if (child_pid != pid){
        track_pid(session_name, child_pid);
        g_array_append_val(allowed_pids, child_pid);
      }
    }
  }
}

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("[ERROR - lttng-noty] Please provide a session name argument and a parent pid.\n");
    return 1;
  }
  char *session_name = strdup(argv[1]);
  pid_t ppid = atoi(argv[2]);
  GArray *allowed_pids = g_array_new(FALSE, FALSE, sizeof(pid_t));
  g_array_append_val(allowed_pids, ppid);

  struct lttng_notification_channel *notification_channel =
      lttng_notification_channel_create(lttng_session_daemon_notification_endpoint);
  assert(notification_channel);

  printf("[INFO - lttng-noty] Created notification channel\n");
  int subscribed = subscribe_fork_triggers(notification_channel);
  if (!subscribed) {
    printf("[ERROR - lttng-noty] Failed to subscribe fork triggers\n");
    return 1;
  }

  bool loop = true;
  while (loop) {
    struct lttng_notification *notification;
    enum lttng_notification_channel_status status =
        lttng_notification_channel_get_next_notification(notification_channel, &notification);

    switch (status) {
    case LTTNG_NOTIFICATION_CHANNEL_STATUS_OK:
      break;
    case LTTNG_NOTIFICATION_CHANNEL_STATUS_NOTIFICATIONS_DROPPED:
      continue;
    case LTTNG_NOTIFICATION_CHANNEL_STATUS_CLOSED:
      loop = false;
      continue;
    default:
      printf("[ERROR - lttng-noty] Failed to get next notification on channel: %d\n", status);
      loop = false;
      continue;
    }

    handle_notification(notification, session_name, allowed_pids);
    lttng_notification_destroy(notification);
  }

  lttng_notification_channel_destroy(notification_channel);
  return 0;
}