#include "event.h"

static event_type parse_event_name(const bt_event_class *event_class, char **syscall_name) {
  const char *event_name = bt_event_class_get_name(event_class);
  char **names = g_strsplit(event_name, "_", 3);
  *syscall_name = strdup(names[2]);

  event_type type = event_type_entry;
  if (strcmp(names[1], "exit") == 0) {
    type = event_type_exit;
  }

  g_strfreev(names);
  return type;
}

void destroy_event_arg(struct event_arg *event_arg) {
  switch (event_arg->type) {
  case event_arg_type_str:
    g_free(event_arg->data.str);
    break;
  case event_arg_type_obj:
    g_hash_table_destroy(event_arg->data.p);
    break;
  case event_arg_type_arr:
    g_ptr_array_free(event_arg->data.p, true);
    break;
  default:
    break;
  }
  g_free(event_arg);
}

static struct event_arg *bt_field_to_event_arg(const bt_field *field) {
  struct event_arg *event_arg = g_new0(struct event_arg, 1);
  event_arg->type = event_arg_type_null;

  if (!field) {
    return event_arg;
  }

  bt_field_class_type fc_type = bt_field_get_class_type(field);
  switch (fc_type) {
  case BT_FIELD_CLASS_TYPE_BOOL:
    event_arg->data.b = bt_field_bool_get_value(field);
    event_arg->type = event_arg_type_bool;
    break;
  case BT_FIELD_CLASS_TYPE_BIT_ARRAY:
    event_arg->data.ui = bt_field_bit_array_get_value_as_integer(field);
    event_arg->type = event_arg_type_uint;
    break;
  case BT_FIELD_CLASS_TYPE_UNSIGNED_INTEGER:
    event_arg->data.ui = bt_field_integer_unsigned_get_value(field);
    event_arg->type = event_arg_type_uint;
    break;
  case BT_FIELD_CLASS_TYPE_SIGNED_INTEGER:
    event_arg->data.i = bt_field_integer_signed_get_value(field);
    event_arg->type = event_arg_type_int;
    break;
  case BT_FIELD_CLASS_TYPE_SINGLE_PRECISION_REAL:
    event_arg->data.f = bt_field_real_single_precision_get_value(field);
    event_arg->type = event_arg_type_float;
    break;
  case BT_FIELD_CLASS_TYPE_DOUBLE_PRECISION_REAL:
    event_arg->data.d = bt_field_real_double_precision_get_value(field);
    event_arg->type = event_arg_type_double;
    break;
  case BT_FIELD_CLASS_TYPE_STRING:
    event_arg->data.str = strdup(bt_field_string_get_value(field));
    event_arg->type = event_arg_type_str;
    break;
  case BT_FIELD_CLASS_TYPE_STRUCTURE:
    GHashTable *obj = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroy_event_arg);
    const bt_field_class *fc = bt_field_borrow_class_const(field);
    uint64_t member_count = bt_field_class_structure_get_member_count(fc);
    if (member_count > 0) {
      for (uint64_t i = 0; i < member_count; i++) {
        const bt_field_class_structure_member *member = bt_field_class_structure_borrow_member_by_index_const(fc, i);
        const bt_field *member_field = bt_field_structure_borrow_member_field_by_index_const(field, i);
        g_hash_table_insert(obj, strdup(bt_field_class_structure_member_get_name(member)),
                            bt_field_to_event_arg(member_field));
      }
    }
    event_arg->data.p = obj;
    event_arg->type = event_arg_type_obj;
    break;
  case BT_FIELD_CLASS_TYPE_ARRAY:
  case BT_FIELD_CLASS_TYPE_STATIC_ARRAY:
  case BT_FIELD_CLASS_TYPE_DYNAMIC_ARRAY:
  case BT_FIELD_CLASS_TYPE_DYNAMIC_ARRAY_WITHOUT_LENGTH_FIELD:
  case BT_FIELD_CLASS_TYPE_DYNAMIC_ARRAY_WITH_LENGTH_FIELD:
    GPtrArray *arr = g_ptr_array_new_with_free_func((GDestroyNotify)destroy_event_arg);
    uint64_t length = bt_field_array_get_length(field);
    if (length > 0) {
      for (uint64_t i = 0; i < length; i++) {
        const bt_field *elem_field = bt_field_array_borrow_element_field_by_index_const(field, i);
        g_ptr_array_add(arr, bt_field_to_event_arg(elem_field));
      }
    }
    event_arg->data.p = arr;
    event_arg->type = event_arg_type_arr;
    break;
  case BT_FIELD_CLASS_TYPE_OPTION:
  case BT_FIELD_CLASS_TYPE_OPTION_WITHOUT_SELECTOR_FIELD:
  case BT_FIELD_CLASS_TYPE_OPTION_WITH_SELECTOR_FIELD:
  case BT_FIELD_CLASS_TYPE_OPTION_WITH_BOOL_SELECTOR_FIELD:
  case BT_FIELD_CLASS_TYPE_OPTION_WITH_INTEGER_SELECTOR_FIELD:
  case BT_FIELD_CLASS_TYPE_OPTION_WITH_UNSIGNED_INTEGER_SELECTOR_FIELD:
  case BT_FIELD_CLASS_TYPE_OPTION_WITH_SIGNED_INTEGER_SELECTOR_FIELD:
    return bt_field_to_event_arg(bt_field_option_borrow_field_const(field));
  case BT_FIELD_CLASS_TYPE_VARIANT:
  case BT_FIELD_CLASS_TYPE_VARIANT_WITHOUT_SELECTOR_FIELD:
  case BT_FIELD_CLASS_TYPE_VARIANT_WITH_SELECTOR_FIELD:
  case BT_FIELD_CLASS_TYPE_VARIANT_WITH_INTEGER_SELECTOR_FIELD:
  case BT_FIELD_CLASS_TYPE_VARIANT_WITH_UNSIGNED_INTEGER_SELECTOR_FIELD:
  case BT_FIELD_CLASS_TYPE_VARIANT_WITH_SIGNED_INTEGER_SELECTOR_FIELD:
    return bt_field_to_event_arg(bt_field_variant_borrow_selected_option_field_const(field));
  default:
    break;
  }

  return event_arg;
}

static void write_root_field(const bt_field *root_field, GHashTable *args, char *root_name) {
  if (!root_field)
    return;

  bt_field_class_type fc_type = bt_field_get_class_type(root_field);
  if (fc_type != BT_FIELD_CLASS_TYPE_STRUCTURE)
    return;

  if (root_name) {
    g_hash_table_insert(args, strdup(root_name), bt_field_to_event_arg(root_field));
    return;
  }

  const bt_field_class *fc = bt_field_borrow_class_const(root_field);
  uint64_t member_count = bt_field_class_structure_get_member_count(fc);

  if (member_count > 0) {
    for (uint64_t i = 0; i < member_count; i++) {
      const bt_field_class_structure_member *member = bt_field_class_structure_borrow_member_by_index_const(fc, i);
      const bt_field *member_field = bt_field_structure_borrow_member_field_by_index_const(root_field, i);
      g_hash_table_insert(args, strdup(bt_field_class_structure_member_get_name(member)),
                          bt_field_to_event_arg(member_field));
    }
  }
}

static void write_extra_args(const bt_event *event, GHashTable *args) {
  struct event_arg *tid = g_hash_table_lookup(args, "tid");
  struct event_arg *host = g_hash_table_lookup(args, "hostname");
  if (tid && host && tid->type == event_arg_type_int && host->type == event_arg_type_str) {
    char *thread = g_strdup_printf("%ld@%s", tid->data.i, host->data.str);
    struct event_arg *thread_arg = g_new0(struct event_arg, 1);
    thread_arg->data.str = thread;
    thread_arg->type = event_arg_type_str;
    g_hash_table_insert(args, strdup("thread"), thread_arg);
  }

  const bt_trace *trace = bt_stream_borrow_trace_const(bt_event_borrow_stream_const(event));
  const bt_value *trace_name = bt_trace_borrow_environment_entry_value_by_name_const(trace, "trace_name");
  if (trace_name && bt_value_is_string(trace_name)) {
    struct event_arg *session_name_arg = g_new0(struct event_arg, 1);
    session_name_arg->data.str = strdup(bt_value_string_get(trace_name));
    session_name_arg->type = event_arg_type_str;
    g_hash_table_insert(args, strdup("session_name"), session_name_arg);
  }

  const bt_packet *packet = bt_event_borrow_packet_const(event);
  const bt_field *packet_context_field = bt_packet_borrow_context_field_const(packet);
  if (bt_field_get_class_type(packet_context_field) == BT_FIELD_CLASS_TYPE_STRUCTURE) {
    const bt_field *cpu_id = bt_field_structure_borrow_member_field_by_name_const(packet_context_field, "cpu_id");
    if (cpu_id) {
      g_hash_table_insert(args, strdup("cpu"), bt_field_to_event_arg(cpu_id));
    }
  }
}

void destroy_event_record(struct event_record *event_rec) {
  g_free(event_rec->name);
  g_free(event_rec->ts);
  g_hash_table_destroy(event_rec->args);
  g_free(event_rec);
}

struct event_record *event_message_to_event_record(const bt_message *msg) {
  struct event_record *event_rec = g_new0(struct event_record, 1);
  event_rec->args = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroy_event_arg);

  const bt_event *event = bt_message_event_borrow_event_const(msg);
  const bt_event_class *event_class = bt_event_borrow_class_const(event);
  const bt_clock_snapshot *clock_snapshot = bt_message_event_borrow_default_clock_snapshot_const(msg);

  char *syscall_name;
  event_type type = parse_event_name(event_class, &syscall_name);
  event_rec->type = type;
  event_rec->name = strdup(syscall_name);
  g_free(syscall_name);

  struct timestamp *ts = clock_snapshot_to_timestamp(clock_snapshot);
  event_rec->ts = ts;

  // parse common context fields
  write_root_field(bt_event_borrow_common_context_field_const(event), event_rec->args, NULL);

  // parse specific context fields
  write_root_field(bt_event_borrow_specific_context_field_const(event), event_rec->args, NULL);

  // parse payload fields
  write_root_field(bt_event_borrow_payload_field_const(event), event_rec->args, "args");

  write_extra_args(event, event_rec->args);

  return event_rec;
}

static struct json_object *event_arg_to_json_object(struct event_arg *event_arg);

static void arr_iter_func(gpointer event_arg, gpointer json_obj_arr) {
  json_object_array_add(json_obj_arr, event_arg_to_json_object(event_arg));
}

static void hash_iter_func(gpointer name, gpointer event_arg, gpointer json_obj) {
  json_object_object_add(json_obj, name, event_arg_to_json_object(event_arg));
}

static struct json_object *event_arg_to_json_object(struct event_arg *event_arg) {
  if (!event_arg) {
    return json_object_new_null();
  }

  switch (event_arg->type) {
  case event_arg_type_int:
    return json_object_new_int64(event_arg->data.i);
  case event_arg_type_uint:
    return json_object_new_uint64(event_arg->data.ui);
  case event_arg_type_str:
    return json_object_new_string(event_arg->data.str);
  case event_arg_type_bool:
    return json_object_new_boolean(event_arg->data.b);
  case event_arg_type_float:
    return json_object_new_double((double)event_arg->data.d);
  case event_arg_type_double:
    return json_object_new_double(event_arg->data.d);
  case event_arg_type_arr:
    struct json_object *json_arr = json_object_new_array();
    GPtrArray *arr = (GPtrArray *)event_arg->data.p;
    g_ptr_array_foreach(arr, (GFunc)arr_iter_func, json_arr);
    return json_arr;
  case event_arg_type_obj:
    struct json_object *json_obj = json_object_new_object();
    GHashTable *hash_table = (GHashTable *)event_arg->data.p;
    g_hash_table_foreach(hash_table, (GHFunc)hash_iter_func, json_obj);
    return json_obj;
  default:
    return json_object_new_null();
  }
}

static void hash_merge_iter_func(char *name, struct event_arg *event_arg, struct json_object *json_obj) {
  struct json_object *existed;

  if (!json_object_object_get_ex(json_obj, name, &existed)) {
    json_object_object_add(json_obj, name, event_arg_to_json_object(event_arg));
  } else if (event_arg->type == event_arg_type_obj) {
    g_hash_table_foreach(event_arg->data.p, (GHFunc)hash_merge_iter_func, existed);
  }
}

static void transform_address_family(json_object *args) {
  struct json_object *family;
  if (json_object_object_get_ex(args, "family", &family) && json_object_is_type(family, json_type_int)) {
    struct json_object *address_family = json_object_new_string(get_address_family_name(json_object_get_int64(family)));
    json_object_object_del(args, "family");
    json_object_object_add(args, "family", address_family);
  }
}

static void transform_socket_type(json_object *args) {
  struct json_object *type;
  if (json_object_object_get_ex(args, "type", &type) && json_object_is_type(type, json_type_int)) {
    struct json_object *socket_type = json_object_new_string(get_socket_type(json_object_get_int64(type)));
    json_object_object_del(args, "type");
    json_object_object_add(args, "type", socket_type);
  }
}

static void transform_protocol(json_object *args) {
  struct json_object *family, *protocol;
  if (json_object_object_get_ex(args, "family", &family) && json_object_is_type(family, json_type_int) &&
      json_object_object_get_ex(args, "protocol", &protocol) && json_object_is_type(protocol, json_type_int)) {
    struct json_object *protocol_name =
        json_object_new_string(get_protocol_name(json_object_get_int64(family), json_object_get_int64(protocol)));
    json_object_object_del(args, "protocol");
    json_object_object_add(args, "protocol", protocol_name);
  }
}

static void transform_level_optname(json_object *args) {
  struct json_object *level, *optname;
  if (json_object_object_get_ex(args, "level", &level) && json_object_is_type(level, json_type_int)) {
    int64_t opt = -1;
    if (json_object_object_get_ex(args, "optname", &optname) && json_object_is_type(optname, json_type_int)) {
      opt = json_object_get_int64(optname);
    }
    char *level_opt[2];
    get_level_optname_name(json_object_get_int64(level), opt, level_opt);
    json_object_object_del(args, "level");
    json_object_object_add(args, "level", json_object_new_string(level_opt[0]));
    if (opt != -1) {
      json_object_object_del(args, "optname");
      json_object_object_add(args, "optname", json_object_new_string(level_opt[1]));
    }
  }
}

static void transform_flags(char *syscall_name, json_object *args) {
  if (strcmp(syscall_name, "creat") == 0) {
    json_object_object_del(args, "flags");
    json_object_object_add(args, "flags", json_object_new_string("O_CREAT|O_WRONLY|O_TRUNC"));
    return;
  }

  struct json_object *flags;
  if (json_object_object_get_ex(args, "flags", &flags) && json_object_is_type(flags, json_type_int)) {
    if (strcmp(syscall_name, "open") == 0 || strcmp(syscall_name, "openat") == 0) {
      json_object_object_del(args, "flags");
      json_object_object_add(args, "flags", json_object_new_string(get_open_flags(json_object_get_int64(flags))));
    }
  }
}

static void transform_mode(char *syscall_name, json_object *args) {
  struct json_object *flags, *mode;
  if (json_object_object_get_ex(args, "flags", &flags) && json_object_is_type(flags, json_type_int) &&
      json_object_object_get_ex(args, "mode", &mode) && json_object_is_type(mode, json_type_int)) {
    if (strcmp(syscall_name, "open") == 0 || strcmp(syscall_name, "openat") == 0 ||
        strcmp(syscall_name, "creat") == 0) {
      json_object_object_del(args, "mode");
      const char *mode_string = get_creation_mode(json_object_get_int64(flags), json_object_get_int64(mode));
      if (mode_string) {
        json_object_object_add(args, "mode", json_object_new_string(mode_string));
      }
    }
  }
}

static void transform_args(char *syscall_name, struct json_object *json) {
  struct json_object *args;

  if (!json_object_object_get_ex(json, "args", &args))
    return;
  if (!json_object_is_type(args, json_type_object))
    return;

  transform_address_family(args);
  transform_level_optname(args);
  transform_socket_type(args);
  transform_protocol(args);
  transform_flags(syscall_name, args);
  transform_mode(syscall_name, args);
}

struct json_object *create_syscall_json_object(struct event_record *entry_rec, struct event_record *exit_rec) {
  struct json_object *json = json_object_new_object();
  json_object_object_add(json, "system_call_name", json_object_new_string(entry_rec->name));

  json_object_object_add(json, "call_timestamp", json_object_new_uint64(uint64_timestamp(entry_rec->ts)));
  char *time_called = timestamp_to_string(entry_rec->ts);
  json_object_object_add(json, "time_called", json_object_new_string(time_called));
  g_free(time_called);

  json_object_object_add(json, "return_timestamp", json_object_new_uint64(uint64_timestamp(exit_rec->ts)));
  char *time_returned = timestamp_to_string(exit_rec->ts);
  json_object_object_add(json, "time_returned", json_object_new_string(time_returned));
  g_free(time_returned);

  double diff_ts = calc_time_diff(exit_rec->ts, entry_rec->ts);
  json_object_object_add(json, "execution_time", json_object_new_double(diff_ts));

  json_object_object_add(json, "category", json_object_new_string(get_metadata_category(entry_rec->name)));
  json_object_object_add(json, "event_type", json_object_new_string(get_metadata_event_type(entry_rec->name)));
  json_object_object_add(json, "type", json_object_new_string(get_metadata_func_type(entry_rec->name)));

  g_hash_table_foreach(entry_rec->args, (GHFunc)hash_merge_iter_func, json);
  g_hash_table_foreach(exit_rec->args, (GHFunc)hash_merge_iter_func, json);

  if (TRANSFORM_ARGUMENTS) {
    transform_args(entry_rec->name, json);
  }

  return json;
}