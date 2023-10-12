#!/bin/bash

set -e

ELASTIC_PLUGIN_DIR=/usr/share/babeltrace2/elastic-plugin/
BABELTRACE_SINK_COMPONENT=elastic.elastic_sink

# default values

: ${BABELTRACE_DUMMY:="False"}
: ${LTTNG_LIVE:="True"}

cd $ELASTIC_PLUGIN_DIR

get_live_url() {
  LIVE_URL=$(babeltrace2 -i lttng-live net://$LTTNG_ADDRESS 2> /dev/null | awk {'print $1'})
}

if [ $LTTNG_LIVE = "True" ]; then
  echo Searching for connections on $LTTNG_ADDRESS
  while [ -z "$LIVE_URL" ]
  do
    get_live_url
  done
  
  echo Found connection on $LIVE_URL
  echo Connecting babeltrace2 to $LIVE_URL
  TRACE_URL="-i lttng-live $LIVE_URL"
else
  TRACE_URL="/tmp/lttng-traces/"
fi

# Clock start
START=`date +%s`

if [ $BABELTRACE_DUMMY = "True" ]; then
  echo Using default sink component
  
  if [ $BABELTRACE_DISCARD = "True" ]; then
    babeltrace2 --plugin-path=. $TRACE_URL | tee /dev/null | wc -l
  else
    babeltrace2 --plugin-path=. $TRACE_URL | tee >(wc -l)
  fi
else
  babeltrace2 --plugin-path=. $TRACE_URL --component sink.$BABELTRACE_SINK_COMPONENT 
fi

# Clock end
END=`date +%s`
RUNTIME=$((END-START))

echo babeltrace2 runtime: $RUNTIME"s ~" $((RUNTIME / 60))m$((RUNTIME % 60))s