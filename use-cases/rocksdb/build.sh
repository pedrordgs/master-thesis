#!/bin/sh

docker build . -t pedrordgs/lttng_rocksdb:latest
docker push pedrordgs/lttng_rocksdb:latest