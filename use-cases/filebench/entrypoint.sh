#!/bin/bash

set -e 

# Disable randomize va space to be able to run filebench
sysctl kernel.randomize_va_space=0

# Run lttng entrypoint
exec /usr/share/lttng-tracer/entrypoint.sh "$@"