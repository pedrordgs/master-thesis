#!/bin/bash

set -e
set -m

LTTNG_SESSION_NAME="sample-session"
LTTNG_SYSCALLS="open;openat;creat;read;pread;readv;write;pwrite;close"

ES_URL="http://192.168.112.73:31111"
ES_USER="dio"
ES_PWD="diopw"

ROCKSDB_LOAD=100000000
DB_BENCH_OPS=100000000 

mkdir -p /home/gsd/use-cases/results/rocksdb/

LOAD_CONTAINER="docker run -it -d --name rocksdb --pid=host --privileged --cap-add=ALL --net=host -v /lib/modules:/lib/modules -v /usr/src:/usr/src -v /sys/kernel/debug/:/sys/kernel/debug/ -v /tmp/lttng-traces/:/tmp/lttng-traces/ -v /home/gsd/use-cases/rocksdb/kvstore:/rocksdb/test/kvstore -v /home/gsd/use-cases/results/rocksdb:/rocksdb/test/results -e LTTNG_SESSION_NAME=$LTTNG_SESSION_NAME -e LTTNG_SYSCALLS='$LTTNG_SYSCALLS' -e LTTNG_TRACEPOINTS= -e LTTNG_EXTRA_CONTEXT='pid;tid;hostname;procname;ppid' -e LTTNG_LIVE=True -e LTTNG_DEFAULT=False -e POST_TRACE_ANALYSIS=False -e ROCKSDB_LOAD=$ROCKSDB_LOAD -e DB_BENCH_OPS=$DB_BENCH_OPS pedrordgs/lttng_rocksdb:latest load"
YCSBWA_CONTAINER="docker run -it -d --name rocksdb --pid=host --privileged --cap-add=ALL --net=host -v /lib/modules:/lib/modules -v /usr/src:/usr/src -v /sys/kernel/debug/:/sys/kernel/debug/ -v /tmp/lttng-traces/:/tmp/lttng-traces/ -v /home/gsd/use-cases/rocksdb/kvstore:/rocksdb/test/kvstore -v /home/gsd/use-cases/results/rocksdb:/rocksdb/test/results -e LTTNG_SESSION_NAME=$LTTNG_SESSION_NAME -e LTTNG_SYSCALLS='$LTTNG_SYSCALLS' -e LTTNG_TRACEPOINTS= -e LTTNG_EXTRA_CONTEXT='pid;tid;hostname;procname;ppid' -e LTTNG_LIVE=True -e LTTNG_DEFAULT=False -e POST_TRACE_ANALYSIS=False -e ROCKSDB_LOAD=$ROCKSDB_LOAD -e DB_BENCH_OPS=$DB_BENCH_OPS pedrordgs/lttng_rocksdb:latest ycsbwa"
BABELTRACE_CONTAINER="docker run -it -d --name babel --net=host -v /tmp/lttng-traces/:/tmp/lttng-traces/ -e ES_ADDRESSES=$ES_URL -e ES_USER=$ES_USER -e ES_PWD=$ES_PWD -e ES_INDEX_NAME=dio_trace -e LTTNG_ADDRESS=127.0.0.1 -e ELK_ENABLED=True -e BABELTRACE_DUMMY=False -e LTTNG_LIVE=True pedrordgs/babeltrace:latest"
CURRENT_CONTAINER=$YCSBWA_CONTAINER

function test {
    echo "---- Starting babeltrace2 container ($1 - $RUN)"
    $BABELTRACE_CONTAINER
    echo "---- Starting rocksdb container ($1 - $RUN)"
    $CURRENT_CONTAINER
    docker container wait babel
    docker stop rocksdb
    docker logs rocksdb > /home/gsd/use-cases/results/rocksdb/rocksdb_docker_logs_$RUN.txt 2>&1
    docker logs babel > /home/gsd/use-cases/results/rocksdb/babel_docker_logs_$RUN.txt 2>&1
    docker rm rocksdb babel
}

function load {
    echo ">> Running load test ($RUN)"
    CURRENT_CONTAINER=$LOAD_CONTAINER
    test "load"
    echo "<< Done"
}

function ycsbwa {
    echo ">> Running ycsbwa test ($RUN)"
    CURRENT_CONTAINER=$YCSBWA_CONTAINER
    test "ycsbwa"
    echo "<< Done"
}

function delete_indexes {
    curl -u "$ES_USER:$ES_PWD" -k -X DELETE "$ES_URL/dio*?pretty"
    sudo sh -c "echo 3 >'/proc/sys/vm/drop_caches' && swapoff -a && swapon -a && rm -rf /tmp/lttng-traces/ && rm -rf /home/gsd/use-cases/rocksdb/kvstore  && printf '\n%s\n' 'Ram-cache and Swap Cleared'"
}

# run_test <test> <runs>
function run_test {
    TEST=$1
    RUNS=$2
    for i in $(seq 1 $RUNS);
    do
        delete_indexes
        RUN=$i
        echo "!! Starting run $RUN"
        $TEST
    done
}

$@