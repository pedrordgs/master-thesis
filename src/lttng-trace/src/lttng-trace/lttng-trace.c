#include "lttng-trace.h"

static void run_command(char *command) {
  char *argv[100];
  int argc = 0;
  char *str = strtok(command, " ");
  while (str != NULL) {
    argv[argc++] = strdup(str);
    str = strtok(NULL, " ");
  }
  argv[argc] = NULL;
  printf("[INFO] Running command %s\n", command);
  execvp(argv[0], argv);
}

static struct lttng_handle *create_handle(char *session_name, enum lttng_domain_type type,
                                          enum lttng_buffer_type buf_type) {
  struct lttng_domain *domain = g_new0(struct lttng_domain, 1);
  domain->type = type;
  domain->buf_type = buf_type;
  struct lttng_handle *handle = lttng_create_handle(session_name, domain);
  if (!handle) {
    printf("[WARNING] Failed to create handle for kernel domain.\n");
  }

  return handle;
}

static void create_session(char *session_name) {
  int status;
  if (strcmp(getenv("LTTNG_LIVE"), "True") == 0) {
    status = lttng_create_session_live(session_name, "net://127.0.0.1", 1000000);
  } else {
    char *trace_path = g_strdup_printf("/tmp/lttng-traces/%s", session_name);
    status = lttng_create_session(session_name, trace_path);
  }
  if (status != 0) {
    printf("[ERROR] Failed to create %s live session: %s\n", session_name, lttng_strerror(status));
    exit(1);
  };
}

static void enable_event(char *session_name, char *event_name, enum lttng_event_type type) {
  struct lttng_handle *handle = create_handle(session_name, LTTNG_DOMAIN_KERNEL, LTTNG_BUFFER_GLOBAL);
  struct lttng_event *ev = lttng_event_create();
  strncpy(ev->name, event_name, LTTNG_SYMBOL_NAME_LEN);
  ev->type = type;
  ev->loglevel_type = LTTNG_EVENT_LOGLEVEL_ALL;
  int status = lttng_enable_event_with_filter(handle, ev, NULL, LTTNG_EVENT_FILTER);
  if (status != 0) {
    printf("[WARNING] Failed to enable event %s: %s\n", event_name, lttng_strerror(status));
  }
}

static void add_context(char *session_name, enum lttng_event_context_type ctx_type) {
  struct lttng_handle *handle = create_handle(session_name, LTTNG_DOMAIN_KERNEL, LTTNG_BUFFER_GLOBAL);
  struct lttng_event_context *ctx = g_new0(struct lttng_event_context, 1);
  ctx->ctx = ctx_type;
  int status = lttng_add_context(handle, ctx, NULL, NULL);
  if (status != 0) {
    printf("[WARNING] Failed to add context %d: %s\n", ctx_type, lttng_strerror(status));
  }
}

static void track_pid(const char *session_name, pid_t pid) {
  struct lttng_process_attr_tracker_handle *tracker_handle;
  int status = lttng_session_get_tracker_handle(session_name, LTTNG_DOMAIN_KERNEL, LTTNG_PROCESS_ATTR_PROCESS_ID,
                                                &tracker_handle);
  if (status != LTTNG_OK) {
    printf("[ERROR] Failed to get tracker handle for pid %d: %s\n", pid, lttng_strerror(-status));
    return;
  }
  status = lttng_process_attr_tracker_handle_set_tracking_policy(tracker_handle, LTTNG_TRACKING_POLICY_INCLUDE_SET);
  if (status != LTTNG_PROCESS_ATTR_TRACKER_HANDLE_STATUS_OK) {
    printf("[ERROR] Failed to set tracking policy: %d\n", status);
  }
  status = lttng_process_attr_process_id_tracker_handle_add_pid(tracker_handle, pid);
  if (status != LTTNG_PROCESS_ATTR_TRACKER_HANDLE_STATUS_OK) {
    printf("[ERROR] Failed to add pid to tracker %d: %d\n", pid, status);
  } else {
    printf("[INFO] Added pid %d to tracker for %s\n", pid, session_name);
  }
  lttng_process_attr_tracker_handle_destroy(tracker_handle);
}

static void add_fork_triggers(char *session_name) {
  struct lttng_action *noty_action = lttng_action_notify_create();
  struct lttng_event_rule *event_rule = lttng_event_rule_kernel_tracepoint_create();

  int status = lttng_event_rule_kernel_tracepoint_set_name_pattern(event_rule, PROCESS_FORK_TRIGGER_PATTERN);
  if (status != LTTNG_EVENT_RULE_STATUS_OK) {
    printf("[WARNING] Failed to set kernel tracepoint name for %s: %d\n", PROCESS_FORK_TRIGGER_PATTERN, status);
  }
  struct lttng_condition *condition = lttng_condition_event_rule_matches_create(event_rule);
  status = lttng_condition_event_rule_matches_append_capture_descriptor(
      condition, lttng_event_expr_channel_context_field_create("pid"));
  if (status != LTTNG_CONDITION_STATUS_OK) {
    printf("[WARNING] Failed to append pid to condition capture descriptor: %d\n", status);
  }
  status = lttng_condition_event_rule_matches_append_capture_descriptor(
      condition, lttng_event_expr_event_payload_field_create("child_pid"));
  if (status != LTTNG_CONDITION_STATUS_OK) {
    printf("[WARNING] Failed to append child_pid to condition capture descriptor: %d\n", status);
  }
  struct lttng_trigger *trigger = lttng_trigger_create(condition, noty_action);
  status = lttng_register_trigger_with_name(trigger, PROCESS_FORK_TRIGGER_NAME);
  if (status != LTTNG_OK) {
    printf("[WARNING] Failed to register trigger for %s: %s\n", PROCESS_FORK_TRIGGER_NAME, lttng_strerror(-status));
  } else {
    printf("[INFO] Registered trigger: %s, %s\n", PROCESS_FORK_TRIGGER_NAME, PROCESS_FORK_TRIGGER_PATTERN);
  }
  lttng_condition_destroy(condition);
  lttng_trigger_destroy(trigger);
  lttng_event_rule_destroy(event_rule);
  lttng_action_destroy(noty_action);
}

static void unregister_fork_triggers() {
  struct lttng_triggers *triggers = NULL;
  int found = 0;
  int status = lttng_list_triggers(&triggers);
  if (status != LTTNG_OK) {
    printf("[ERROR] Failed to list triggers: %s\n", lttng_strerror(status));
  }

  unsigned int trigger_count;
  status = lttng_triggers_get_count(triggers, &trigger_count);
  if (status != LTTNG_TRIGGER_STATUS_OK) {
    printf("[ERROR] Failed to get triggers count: %d\n", status);
  }

  for (unsigned int i = 0; i < trigger_count && !found; i++) {
    const struct lttng_trigger *trigger = lttng_triggers_get_at_index(triggers, i);
    const char *trigger_name;
    status = lttng_trigger_get_name(trigger, &trigger_name);
    if (status != LTTNG_TRIGGER_STATUS_OK) {
      printf("[ERROR] Failed to get trigger name: %d\n", status);
    }

    if (strcmp(trigger_name, PROCESS_FORK_TRIGGER_NAME) == 0) {
      status = lttng_unregister_trigger(trigger);
      if (status != 0) {
        printf("[ERROR] Failed to unregister trigger %s: %s\n", trigger_name, lttng_strerror(status));
      } else {
        printf("[INFO] Unregistered trigger %s\n", trigger_name);
      }
      found = 1;
    }
  }

  lttng_triggers_destroy(triggers);
}

static void enable_syscall(gpointer syscall, gpointer session_name) {
  enable_event(session_name, syscall, LTTNG_EVENT_SYSCALL);
}

static void enable_tracepoint(gpointer tracepoint, gpointer session_name) {
  enable_event(session_name, tracepoint, LTTNG_EVENT_TRACEPOINT);
}

static void add_context_type(gpointer ctx_type, gpointer session_name) {
  if (strcmp(ctx_type, "pid") == 0) {
    add_context(session_name, LTTNG_EVENT_CONTEXT_PID);
  } else if (strcmp(ctx_type, "tid") == 0) {
    add_context(session_name, LTTNG_EVENT_CONTEXT_TID);
  } else if (strcmp(ctx_type, "hostname") == 0) {
    add_context(session_name, LTTNG_EVENT_CONTEXT_HOSTNAME);
  } else if (strcmp(ctx_type, "procname") == 0) {
    add_context(session_name, LTTNG_EVENT_CONTEXT_PROCNAME);
  } else if (strcmp(ctx_type, "ppid") == 0) {
    add_context(session_name, LTTNG_EVENT_CONTEXT_PPID);
  }
}

static void prepare_lttng_session(struct opts *opts) {
  g_ptr_array_foreach(opts->syscalls, (GFunc)enable_syscall, opts->session_name);
  g_ptr_array_foreach(opts->tracepoints, (GFunc)enable_tracepoint, opts->session_name);
  g_ptr_array_foreach(opts->ctx_types, (GFunc)add_context_type, opts->session_name);
}

static pid_t create_child_process(char *session_name, char *command) {
  pid_t pid = fork();
  if (pid == 0) {
    raise(SIGSTOP);
    run_command(command);
  } else {
    track_pid(session_name, pid);
    add_fork_triggers(session_name);
  }
  return pid;
}

static void start_tracing(struct opts *opts) {
  pid_t child_pid = 0;
  create_session(opts->session_name);
  if (opts->exec_command) {
    child_pid = create_child_process(opts->session_name, opts->exec_command);
    pid_t pid = fork();
    if (pid == 0) {
      char *lttng_noty_commad = g_strdup_printf("lttng-noty %s %d", opts->session_name, child_pid);
      run_command(lttng_noty_commad);
    }
  }
  if (opts->filter_tid) {
    track_pid(opts->session_name, atoi(opts->filter_tid));
  }
  prepare_lttng_session(opts);
  int status = lttng_start_tracing(opts->session_name);
  if (status != 0) {
    printf("[ERROR] Failed to start tracing session %s: %s\n", opts->session_name, lttng_strerror(status));
    status = lttng_destroy_session(opts->session_name);
    if (status != 0) {
      printf("[ERROR] Failed to destroy tracing session %s: %s\n", opts->session_name, lttng_strerror(status));
    }
    unregister_fork_triggers();
    exit(1);
  }
  if (child_pid) {
    sleep(2);
    kill(child_pid, SIGCONT);
    wait(NULL);
    // get session stats
    printf("%s\n", get_session_stats_str(opts->session_name));
    status = lttng_destroy_session(opts->session_name);
    if (status != 0) {
      printf("[ERROR] Failed to destroy tracing session %s: %s\n", opts->session_name, lttng_strerror(status));
    }
    unregister_fork_triggers();
  }
}

static GPtrArray *get_array_from_env(char *env, char *delimiter) {
  GPtrArray *arr = g_ptr_array_new();
  char *env_str = getenv(env);
  char *token = strtok(env_str, delimiter);
  while (token) {
    g_ptr_array_add(arr, token);
    token = strtok(NULL, delimiter);
  }
  return arr;
}

static struct opts *get_opts() {
  struct opts *opts = g_new0(struct opts, 1);
  opts->session_name = getenv("LTTNG_SESSION_NAME");
  opts->syscalls = get_array_from_env("LTTNG_SYSCALLS", ";");
  opts->tracepoints = get_array_from_env("LTTNG_TRACEPOINTS", ";");
  opts->ctx_types = get_array_from_env("LTTNG_EXTRA_CONTEXT", ";");
  return opts;
}

int main(int argc, char **argv) {
  struct opts *opts = get_opts();
  opts->filter_tid = getenv("FILTER_TID");
  if (argc > 1) {
    opts->exec_command = argv[1];
    printf("[INFO] Tracing command %s\n", opts->exec_command);
  }
  start_tracing(opts);
  return 0;
}