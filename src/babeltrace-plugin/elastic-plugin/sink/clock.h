#ifndef ELASTIC_CLOCK_H
#define ELASTIC_CLOCK_H

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <babeltrace2/babeltrace.h>
#include <glib.h>
#include <time.h>

#define NSEC_PER_SEC 1000000000

struct timestamp {
  time_t ts_sec;
  uint64_t ts_nsec;
};

struct timestamp *clock_snapshot_to_timestamp(const bt_clock_snapshot *clock_snapshot);
double calc_time_diff(struct timestamp *ts_end, struct timestamp *ts_start);
char *timestamp_to_string(struct timestamp *ts);
struct timestamp *clone_ts(struct timestamp *ts);
uint64_t uint64_timestamp(struct timestamp *ts);

#endif