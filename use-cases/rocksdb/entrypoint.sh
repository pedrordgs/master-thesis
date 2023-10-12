#!/bin/bash

set -e
set -m

DB_BENCH_COMMAND="/rocksdb/workloads/exec_workload.sh"

function check_workload() {
    if [ $1 == "load" ]; then
        DB_BENCH_COMMAND="/rocksdb/workloads/exec_workload.sh fillrandom 8 8 1024 fillrandom-8-8-1024"
    elif [ $1 == "ycsbwa" ]; then
        DB_BENCH_COMMAND="/rocksdb/workloads/exec_workload.sh ycsbwklda 8 8 1024 ycsbwklda-8-8-1024"
    else
        echo "Invalid workload"
        exit 1
    fi
}

if [ $# -eq 0 ]; then
    echo "No arguments supplied"
    exit 1
fi

check_workload $1

# Run lttng entrypoint
exec /usr/share/lttng-tracer/entrypoint.sh $DB_BENCH_COMMAND