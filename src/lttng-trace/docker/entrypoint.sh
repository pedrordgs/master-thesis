#!/bin/bash

set -e

# Start lttng session and relay daemnon
lttng-sessiond -d

# default values

: ${LTTNG_LIVE:="True"}
: ${LTTNG_DEFAULT:="False"}
: ${POST_TRACE_ANALYSIS:="False"}

if [ $LTTNG_LIVE = "True" ]; then
  lttng-relayd -d -L tcp://0.0.0.0:5344 -o /tmp/lttng-traces/
fi

# Clock start
START=`date +%s`

if [ $LTTNG_DEFAULT = "True" ]; then
  echo Using default LTTng
  if [ $LTTNG_LIVE = "True" ]; then
    PARAMS="--live"
  else
    PARAMS="--output=/tmp/lttng-traces/"
  fi
  lttng create $LTTNG_SESSION_NAME $PARAMS
  lttng add-context -k -t=pid -t=tid -t=hostname -t=procname -t=ppid # force this and ignore LTTNG_EXTRA_CONTENT
  lttng enable-event -k --syscall ${LTTNG_SYSCALLS//;/,} -f '$ctx.procname != "lttng*"'
  lttng start
  $@
  lttng destroy
else
  lttng-trace "$(echo "$@")"
fi

# Clock end
END=`date +%s`
RUNTIME=$((END-START))

echo LTTng runtime: $RUNTIME"s ~" $((RUNTIME / 60))m$((RUNTIME % 60))s

if [ $POST_TRACE_ANALYSIS != "True" ]; then
  tail -f /dev/null
fi