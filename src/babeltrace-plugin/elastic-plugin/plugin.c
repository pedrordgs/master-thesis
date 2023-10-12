#include <babeltrace2/babeltrace.h>

#include "sink/sink.h"

static bt_plugin_initialize_func_status plugin_initialize_fun(bt_self_plugin *self_plugin) {
  return BT_PLUGIN_INITIALIZE_FUNC_STATUS_OK;
}

static void plugin_finalize_fun() { }

// https://babeltrace.org/docs/v2.0/libbabeltrace2/group__api-plugin-dev.html

/** Define plugin metadata **/

#ifndef BT_BUILT_IN_PLUGINS
BT_PLUGIN_MODULE();
#endif

BT_PLUGIN(elastic);
BT_PLUGIN_AUTHOR("haslab");
BT_PLUGIN_DESCRIPTION("Send trace data to elastic search");
BT_PLUGIN_LICENSE("MIT");

BT_PLUGIN_INITIALIZE_FUNC(plugin_initialize_fun);
BT_PLUGIN_FINALIZE_FUNC(plugin_finalize_fun);

/* Plugin sink component */
BT_PLUGIN_SINK_COMPONENT_CLASS(elastic_sink, elastic_consume);
BT_PLUGIN_SINK_COMPONENT_CLASS_DESCRIPTION(elastic_sink,
                                           "Elastic plugin sink component that parses event data and sends it to "
                                           "elastic search.");
BT_PLUGIN_SINK_COMPONENT_CLASS_HELP(elastic_sink, "Elastic plugin sink component help text");
BT_PLUGIN_SINK_COMPONENT_CLASS_INITIALIZE_METHOD(elastic_sink, elastic_init);
BT_PLUGIN_SINK_COMPONENT_CLASS_GRAPH_IS_CONFIGURED_METHOD(elastic_sink, elastic_graph_is_configured);
BT_PLUGIN_SINK_COMPONENT_CLASS_FINALIZE_METHOD(elastic_sink, elastic_finalize);