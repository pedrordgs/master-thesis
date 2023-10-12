#include "sink.h"

static void destroy_elastic_comp(struct elastic_comp *elastic_comp) {
  if (!elastic_comp) {
    goto end;
  }

  BT_MESSAGE_ITERATOR_PUT_REF_AND_RESET(elastic_comp->msg_iter);
  g_hash_table_destroy(elastic_comp->pending_calls);
  g_free(elastic_comp->min_t);
  g_free(elastic_comp->max_t);
  g_free(elastic_comp->trace_name);
  g_free(elastic_comp);

end:
  return;
}

static struct elastic_comp *create_elastic_comp(bt_self_component *self_comp) {
  struct elastic_comp *elastic_comp = g_new0(struct elastic_comp, 1);
  if (!elastic_comp) {
    goto error;
  }

  elastic_comp->pending_calls =
      g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroy_event_record);
  elastic_comp->handled_events = 0;
  elastic_comp->discarded_events = 0;
  elastic_comp->start_ts = time(NULL);

  goto end;

error:
  destroy_elastic_comp(elastic_comp);
  elastic_comp = NULL;

end:
  return elastic_comp;
}

static bt_component_class_initialize_method_status configure_elastic_comp(struct elastic_comp *elastic_comp,
                                                                          const bt_value *params) {
  return BT_COMPONENT_CLASS_INITIALIZE_METHOD_STATUS_OK;
}

bt_component_class_initialize_method_status elastic_init(bt_self_component_sink *self_comp_sink,
                                                         bt_self_component_sink_configuration *config,
                                                         const bt_value *params, void *init_method_data) {
  bt_component_class_initialize_method_status status = BT_COMPONENT_CLASS_INITIALIZE_METHOD_STATUS_OK;
  bt_self_component_add_port_status add_port_status;
  struct elastic_comp *elastic_comp;
  bt_self_component *self_comp = bt_self_component_sink_as_self_component(self_comp_sink);

  elastic_comp = create_elastic_comp(self_comp);
  if (!elastic_comp) {
    BT_CURRENT_THREAD_ERROR_APPEND_CAUSE_FROM_COMPONENT(self_comp, "Failed to allocate elastic component.\n");
    goto error;
  }

  add_port_status = bt_self_component_sink_add_input_port(self_comp_sink, IN_PORT_NAME, NULL, NULL);
  if (add_port_status != BT_SELF_COMPONENT_ADD_PORT_STATUS_OK) {
    BT_CURRENT_THREAD_ERROR_APPEND_CAUSE_FROM_COMPONENT(self_comp, "Failed to add input port on elastic component.\n");
    status = (bt_component_class_initialize_method_status)add_port_status;
    goto error;
  }

  status = configure_elastic_comp(elastic_comp, params);
  if (status != BT_COMPONENT_CLASS_INITIALIZE_METHOD_STATUS_OK) {
    BT_CURRENT_THREAD_ERROR_APPEND_CAUSE_FROM_COMPONENT(self_comp, "Failed to configure elastic component.\n");
    goto error;
  }

  bt_self_component_set_data(self_comp, elastic_comp);
  goto end;

error:
  destroy_elastic_comp(elastic_comp);

end:
  startElasticClient();
  return status;
}

bt_component_class_sink_graph_is_configured_method_status
elastic_graph_is_configured(bt_self_component_sink *self_comp_sink) {
  bt_component_class_sink_graph_is_configured_method_status status;
  bt_message_iterator_create_from_sink_component_status msg_iter_status;
  bt_message_iterator *msg_iter;
  bt_self_component_port_input *in_port;

  bt_self_component *self_comp = bt_self_component_sink_as_self_component(self_comp_sink);
  struct elastic_comp *elastic_comp = bt_self_component_get_data(self_comp);

  in_port = bt_self_component_sink_borrow_input_port_by_name(self_comp_sink, IN_PORT_NAME);
  if (!bt_port_is_connected(bt_port_input_as_port_const(bt_self_component_port_input_as_port_input(in_port)))) {
    BT_CURRENT_THREAD_ERROR_APPEND_CAUSE_FROM_COMPONENT(self_comp, "Single input port is not connected.\n");
  }

  msg_iter_status = bt_message_iterator_create_from_sink_component(self_comp_sink, in_port, &msg_iter);
  if (msg_iter_status != BT_MESSAGE_ITERATOR_CREATE_FROM_SINK_COMPONENT_STATUS_OK) {
    BT_CURRENT_THREAD_ERROR_APPEND_CAUSE_FROM_COMPONENT(self_comp, "Failed to create message iterator.\n");
  }

  BT_MESSAGE_ITERATOR_MOVE_REF(elastic_comp->msg_iter, msg_iter);
  status = BT_COMPONENT_CLASS_SINK_GRAPH_IS_CONFIGURED_METHOD_STATUS_OK;

  return status;
}

static uint64_t consume_event_message(struct elastic_comp *elastic_comp, const bt_message *msg) {
  struct event_record *event_rec = event_message_to_event_record(msg);
  struct event_arg *tid = g_hash_table_lookup(event_rec->args, "tid");
  if (!tid || tid->type != event_arg_type_int)
    return 1;
  char *key = g_strdup_printf("%ld %s", tid->data.i, event_rec->name);

  if (!elastic_comp->min_t || calc_time_diff(event_rec->ts, elastic_comp->min_t) < 0) {
    elastic_comp->min_t = clone_ts(event_rec->ts);
  }
  if (!elastic_comp->max_t || calc_time_diff(elastic_comp->max_t, event_rec->ts) < 0) {
    elastic_comp->max_t = clone_ts(event_rec->ts);
  }
  if (!elastic_comp->trace_name) {
    struct event_arg *trace_name = g_hash_table_lookup(event_rec->args, "session_name");
    if (trace_name && trace_name->type == event_arg_type_str) {
      elastic_comp->trace_name = strdup(trace_name->data.str);
    }
  }

  if (event_rec->type == event_type_entry) {
    g_hash_table_insert(elastic_comp->pending_calls, key, event_rec);
  } else if (event_rec->type == event_type_exit) {
    struct event_record *entry_rec = g_hash_table_lookup(elastic_comp->pending_calls, key);
    if (entry_rec) {
      struct json_object *json = create_syscall_json_object(entry_rec, event_rec);
      sendEventElastic((char *)json_object_to_json_string_ext(json, JSON_C_TO_STRING_NOSLASHESCAPE), false);
      json_object_put(json);
      destroy_event_record(event_rec);
      g_free(key);
      elastic_comp->handled_events++;
    }
    g_hash_table_remove(elastic_comp->pending_calls, key);
  }

  return 0;
}

static void consume_discarded_event_message(struct elastic_comp *elastic_comp, const bt_message *msg) {
  uint64_t count;
  bt_property_availability availability = bt_message_discarded_events_get_count(msg, &count);
  if (availability != BT_PROPERTY_AVAILABILITY_AVAILABLE) {
    count = 1;
  }
  elastic_comp->discarded_events += count;
}

bt_component_class_sink_consume_method_status elastic_consume(bt_self_component_sink *self_comp_sink) {
  bt_component_class_sink_consume_method_status status;
  bt_message_array_const msgs;
  uint64_t count;
  bt_self_component *self_comp = bt_self_component_sink_as_self_component(self_comp_sink);
  struct elastic_comp *elastic_comp = bt_self_component_get_data(self_comp);

  bt_message_iterator_next_status next_status = bt_message_iterator_next(elastic_comp->msg_iter, &msgs, &count);

  if (next_status != BT_MESSAGE_ITERATOR_NEXT_STATUS_OK) {
    status = (bt_component_class_sink_consume_method_status)next_status;
    goto end;
  }

  for (uint64_t i = 0; i < count; i++) {
    bt_message_type msg_type = bt_message_get_type(msgs[i]);
    uint64_t consume_msg_status = 0;

    switch (msg_type) {
    case BT_MESSAGE_TYPE_EVENT:
      consume_msg_status = consume_event_message(elastic_comp, msgs[i]);
      break;
    case BT_MESSAGE_TYPE_DISCARDED_EVENTS:
      consume_discarded_event_message(elastic_comp, msgs[i]);
    default:
      break;
    }

    if (consume_msg_status) {
      for (; i < count; i++) {
        /* Put all remaining messages */
        bt_message_put_ref(msgs[i]);
        BT_CURRENT_THREAD_ERROR_APPEND_CAUSE_FROM_COMPONENT(self_comp, "Failed to consume message.\n");
        status = BT_COMPONENT_CLASS_SINK_CONSUME_METHOD_STATUS_ERROR;
        goto end;
      }
    }

    /* Put this message */
    bt_message_put_ref(msgs[i]);
  }

  status = BT_COMPONENT_CLASS_SINK_CONSUME_METHOD_STATUS_OK;

end:
  return status;
}

void elastic_finalize(bt_self_component_sink *comp) {
  struct elastic_comp *elastic_comp = bt_self_component_get_data(bt_self_component_sink_as_self_component(comp));
  if (elastic_comp->min_t && elastic_comp->max_t && elastic_comp->trace_name) {
    struct json_object *json = json_object_new_object();
    char *min_t = timestamp_to_string(elastic_comp->min_t);
    char *max_t = timestamp_to_string(elastic_comp->max_t);
    json_object_object_add(json, "min_t", json_object_new_string(min_t));
    json_object_object_add(json, "max_t", json_object_new_string(max_t));
    json_object_object_add(json, "duration",
                           json_object_new_double(calc_time_diff(elastic_comp->max_t, elastic_comp->min_t)));
    json_object_object_add(json, "session_name", json_object_new_string(elastic_comp->trace_name));

    char now[50];
    time_t t = time(NULL);
    struct tm *tm = gmtime(&t);
    strftime(now, 50, "%FT%TZ", tm);
    char begin[50];
    struct tm *begin_tm = gmtime(&(elastic_comp->start_ts));
    strftime(begin, 50, "%FT%TZ", begin_tm);
    printf(
        "\n\n[%s] Tracing session %s finished:\n\tAnalysis started at: %s\n\tFirst event: %s\n\tLast event: %s\n\tCommand "
        "duration: %f ns\n\tAnalysis ended at: %s\n\tExecution time: %ld s\n\tSystem calls handled: %" PRIu64
        "\n\tDiscarded event messages: %" PRIu64 "\n\n",
        now, elastic_comp->trace_name, begin, min_t, max_t, calc_time_diff(elastic_comp->max_t, elastic_comp->min_t),
        now, t - elastic_comp->start_ts, elastic_comp->handled_events, elastic_comp->discarded_events);
    sendEventElastic((char *)json_object_to_json_string_ext(json, JSON_C_TO_STRING_NOSLASHESCAPE), true);
    g_free(min_t);
    g_free(max_t);
    json_object_put(json);
  }
  closeElasticClient();
  destroy_elastic_comp(elastic_comp);
}