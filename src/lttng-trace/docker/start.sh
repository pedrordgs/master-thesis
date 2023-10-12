#!/bin/bash

set -e

FORKS=5

PIDS=""

for i in $(seq 1 $FORKS);
do
    echo "!! Starting fork: $@ $i"
    $@ &
    PIDS="$PIDS $!"
done

wait $PIDS