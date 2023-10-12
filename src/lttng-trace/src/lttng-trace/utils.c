#include "utils.h"

// Extracted from https://github.com/lttng/lttng-tools/blob/stable-2.13/src/bin/lttng/utils.c

char *get_session_stats_str(const char *session_name) {
  int count, nb_domains, domain_idx, channel_idx, session_idx;
  char *ret = NULL;
  struct lttng_domain *domains = NULL;
  struct lttng_channel *channels = NULL;
  uint64_t discarded_events_total = 0, lost_packets_total = 0;
  struct lttng_session *sessions = NULL;
  const struct lttng_session *selected_session = NULL;
  bool print_discarded_events = false, print_lost_packets = false;

  count = lttng_list_sessions(&sessions);
  if (count < 1) {
    printf("Failed to retrieve session descriptions while printing session statistics.");
    goto end;
  }

  /* Identify the currently-selected sessions. */
  for (session_idx = 0; session_idx < count; session_idx++) {
    if (!strcmp(session_name, sessions[session_idx].name)) {
      selected_session = &sessions[session_idx];
      break;
    }
  }
  if (!selected_session) {
    printf("Failed to retrieve session \"%s\" description while printing session statistics.", session_name);
    goto end;
  }

  nb_domains = lttng_list_domains(session_name, &domains);
  if (nb_domains < 0) {
    goto end;
  }
  for (domain_idx = 0; domain_idx < nb_domains; domain_idx++) {
    struct lttng_handle *handle = lttng_create_handle(session_name, &domains[domain_idx]);

    if (!handle) {
      printf("Failed to create session handle while printing session statistics.");
      goto end;
    }

    free(channels);
    channels = NULL;
    count = lttng_list_channels(handle, &channels);
    for (channel_idx = 0; channel_idx < count; channel_idx++) {
      uint64_t discarded_events = 0, lost_packets = 0;
      struct lttng_channel *channel = &channels[channel_idx];

      int status = lttng_channel_get_discarded_event_count(channel, &discarded_events);
      if (status) {
        printf("Failed to retrieve discarded event count from channel %s", channel->name);
      }

      status = lttng_channel_get_lost_packet_count(channel, &lost_packets);
      if (status) {
        printf("Failed to retrieve lost packet count from channel %s", channel->name);
      }

      discarded_events_total += discarded_events;
      lost_packets_total += lost_packets;
    }
    lttng_destroy_handle(handle);
  }

  print_discarded_events = discarded_events_total > 0 && !selected_session->snapshot_mode;
  print_lost_packets = lost_packets_total > 0 && !selected_session->snapshot_mode;

  if (print_discarded_events && print_lost_packets) {
    ret = g_strdup_printf("Warning: %" PRIu64 " events were discarded and %" PRIu64
                          " packets were lost, please refer to the documentation on channel configuration.",
                          discarded_events_total, lost_packets_total);
  } else if (print_discarded_events) {
    ret = g_strdup_printf("Warning: %" PRIu64
                          " events were discarded, please refer to the documentation on channel configuration.",
                          discarded_events_total);
  } else if (print_lost_packets) {
    ret = g_strdup_printf("Warning: %" PRIu64
                          " packets were lost, please refer to the documentation on channel configuration.",
                          lost_packets_total);
  } else {
    ret = "";
  }
  
end:
  free(sessions);
  free(channels);
  free(domains);
  return ret;
}