#ifndef ELASTIC_SINK_H
#define ELASTIC_SINK_H

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <babeltrace2/babeltrace.h>
#include <glib.h>
#include <json-c/json.h>

#include "clock.h"
#include "elastic-client/elastic_cli.h"
#include "event.h"

#define IN_PORT_NAME "in"

struct elastic_comp {
  bt_message_iterator *msg_iter;
  GHashTable *pending_calls;
  struct timestamp *min_t;
  struct timestamp *max_t;
  char *trace_name;
  uint64_t handled_events;
  uint64_t discarded_events;
  time_t start_ts;
};

bt_component_class_initialize_method_status elastic_init(bt_self_component_sink *component,
                                                         bt_self_component_sink_configuration *config,
                                                         const bt_value *params, void *init_method_data);

bt_component_class_sink_graph_is_configured_method_status
elastic_graph_is_configured(bt_self_component_sink *component);

bt_component_class_sink_consume_method_status elastic_consume(bt_self_component_sink *component);

void elastic_finalize(bt_self_component_sink *component);

#endif