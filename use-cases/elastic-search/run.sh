#!/bin/bash

set -e
set -m

LTTNG_SESSION_NAME="sample-session"
LTTNG_SYSCALLS="read;write;open;close;stat;fstat;lstat;lseek;pread64;pwrite64;readv;writev;socket;connect;accept;sendto;recvfrom;sendmsg;recvmsg;bind;listen;socketpair;setsockopt;getsockopt;fsync;fdatasync;truncate;ftruncate;rename;creat;unlink;readlink;mknod;fstatfs;readahead;setxattr;lsetxattr;fsetxattr;getxattr;lgetxattr;fgetxattr;listxattr;llistxattr;flistxattr;removexattr;lremovexattr;fremovexattr;openat;mknodat;newfstatat;unlinkat;renameat;readlinkat;accept4;renameat2"

ES_URL="http://192.168.112.73:31111"
ES_USER="dio"
ES_PWD="diopw"

mkdir -p /home/gsd/use-cases/results/elasticsearch/

BENCHMARK_CONTAINER="docker run --rm --net=host elastic/rally race --track=geonames --pipeline=benchmark-only --target-hosts=localhost:9200"
LTTNG_CONTAINER="docker run -it -d --name es830 --pid=host --privileged --cap-add=ALL --net=host -v /lib/modules:/lib/modules -v /usr/src:/usr/src -v /sys/kernel/debug/:/sys/kernel/debug/ -v /tmp/lttng-traces/:/tmp/lttng-traces/ -e LTTNG_SESSION_NAME=$LTTNG_SESSION_NAME -e LTTNG_SYSCALLS=$LTTNG_SYSCALLS -e LTTNG_TRACEPOINTS= -e LTTNG_EXTRA_CONTEXT=pid;tid;hostname;procname;ppid -e LTTNG_LIVE=True -e LTTNG_DEFAULT=False pedrordgs/lttng_elasticsearch:latest"
BABELTRACE_CONTAINER="docker run -it -d --name babel --net=host -v /tmp/lttng-traces/:/tmp/lttng-traces/ -e ES_ADDRESSES=$ES_URL -e ES_USER=$ES_USER -e ES_PWD=$ES_PWD -e ES_INDEX_NAME=dio_trace -e LTTNG_ADDRESS=127.0.0.1 -e ELK_ENABLED=True -e BABELTRACE_DUMMY=False -e LTTNG_LIVE=True pedrordgs/babeltrace:latest"

function test {
    echo "---- Starting babeltrace2 container (RUN - $RUN)"
    $BABELTRACE_CONTAINER
    echo "---- Starting elasticsearch container (RUN - $RUN)"
    $LTTNG_CONTAINER
    sleep 120
    echo "---- Starting benchmark container (RUN - $RUN)"
    $BENCHMARK_CONTAINER > /home/gsd/use-cases/results/elasticsearch/bench_results_$RUN.txt 2>&1
    echo "---- Stopping elasticsearch tracing session ($1-$RUN)"
    docker exec es830 lttng destroy $LTTNG_SESSION_NAME
    docker container wait babel
    docker stop es830
    docker logs es830 > /home/gsd/use-cases/results/elasticsearch/es_docker_logs_$RUN.txt 2>&1
    docker logs babel > /home/gsd/use-cases/results/elasticsearch/babel_docker_logs_$RUN.txt 2>&1
    docker rm es830 babel
}

function delete_indexes {
    curl -u "$ES_USER:$ES_PWD" -k -X DELETE "$ES_URL/dio*?pretty"
    sudo sh -c "echo 3 >'/proc/sys/vm/drop_caches' && swapoff -a && swapon -a && rm -rf /tmp/lttng-traces/ && printf '\n%s\n' 'Ram-cache and Swap Cleared'"
}

# run_test <runs>
function run_test {
    RUNS=$1
    for i in $(seq 1 $RUNS);
    do
        delete_indexes
        RUN=$i
        echo "!! Starting run $RUN"
        test
    done
}

$@