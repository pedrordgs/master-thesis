#ifndef ELASTIC_EVENT_H
#define ELASTIC_EVENT_H

#include <inttypes.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <babeltrace2/babeltrace.h>
#include <glib.h>
#include <json-c/json.h>

#include "clock.h"
#include "metadata.h"
#include "network.h"
#include "storage.h"

#define TRANSFORM_ARGUMENTS false

typedef enum event_type { event_type_entry, event_type_exit } event_type;

struct event_record {
  char *name;
  GHashTable *args;
  struct timestamp *ts;
  event_type type;
};

typedef enum event_arg_type {
  event_arg_type_int,
  event_arg_type_uint,
  event_arg_type_str,
  event_arg_type_arr,
  event_arg_type_obj,
  event_arg_type_bool,
  event_arg_type_double,
  event_arg_type_float,
  event_arg_type_null
} event_arg_type;

union data {
  int64_t i;
  uint64_t ui;
  double d;
  float f;
  char *str;
  bool b;
  gpointer p;
};

struct event_arg {
  union data data;
  event_arg_type type;
};

void destroy_event_record(struct event_record *event_rec);
struct event_record *event_message_to_event_record(const bt_message *msg);
struct json_object *create_syscall_json_object(struct event_record *entry_rec, struct event_record *exit_rec);

#endif
