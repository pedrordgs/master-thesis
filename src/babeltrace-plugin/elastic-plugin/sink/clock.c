#include "clock.h"

struct timestamp *clock_snapshot_to_timestamp(const bt_clock_snapshot *clock_snapshot) {
  struct timestamp *ts = NULL;
  if (!clock_snapshot) {
    goto error;
  }

  int64_t ts_nsec = 0;
  int64_t ts_sec = 0;
  uint64_t ts_sec_abs, ts_nsec_abs;

  bt_clock_snapshot_get_ns_from_origin_status ret = bt_clock_snapshot_get_ns_from_origin(clock_snapshot, &ts_nsec);

  if (ret != BT_CLOCK_SNAPSHOT_GET_NS_FROM_ORIGIN_STATUS_OK) {
    goto error;
  }

  ts_sec += ts_nsec / NSEC_PER_SEC;
  ts_nsec = ts_nsec % NSEC_PER_SEC;

  if (ts_sec >= 0 && ts_nsec >= 0) {
    ts_sec_abs = ts_sec;
    ts_nsec_abs = ts_nsec;
  } else if (ts_sec > 0 && ts_nsec < 0) {
    ts_sec_abs = ts_sec - 1;
    ts_nsec_abs = NSEC_PER_SEC + ts_nsec;
  } else if (ts_sec == 0 && ts_nsec < 0) {
    ts_sec_abs = ts_sec;
    ts_nsec_abs = -ts_nsec;
  } else if (ts_sec < 0 && ts_nsec > 0) {
    ts_sec_abs = -(ts_sec + 1);
    ts_nsec_abs = NSEC_PER_SEC - ts_nsec;
  } else if (ts_sec < 0 && ts_nsec == 0) {
    ts_sec_abs = -ts_sec;
    ts_nsec_abs = ts_nsec;
  } else { /* (ts_sec < 0 && ts_nsec < 0) */
    ts_sec_abs = -ts_sec;
    ts_nsec_abs = -ts_nsec;
  }

  ts = g_new0(struct timestamp, 1);
  ts->ts_sec = (time_t)ts_sec_abs;
  ts->ts_nsec = ts_nsec_abs;

  return ts;
error:
  return ts;
}

double calc_time_diff(struct timestamp *ts_end, struct timestamp *ts_start) {
  double diff_sec = difftime(ts_end->ts_sec, ts_start->ts_sec);
  int64_t diff_nsec = ts_end->ts_nsec - ts_start->ts_nsec;
  return diff_sec * NSEC_PER_SEC + diff_nsec;
}

char *timestamp_to_string(struct timestamp *ts) {
  char ts_str[50];
  strftime(ts_str, 50, "%FT%T", gmtime(&(ts->ts_sec)));
  return g_strdup_printf("%s.%luZ", ts_str, ts->ts_nsec);
}

struct timestamp *clone_ts(struct timestamp *ts) {
  struct timestamp *clone = g_new0(struct timestamp, 1);
  clone->ts_sec = ts->ts_sec;
  clone->ts_nsec = ts->ts_nsec;
  return clone;
}

uint64_t uint64_timestamp(struct timestamp *ts) { return (uint64_t)ts->ts_sec * NSEC_PER_SEC + ts->ts_nsec; }