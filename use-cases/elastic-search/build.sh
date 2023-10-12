#!/bin/sh

docker build . -t pedrordgs/lttng_elasticsearch:latest
docker push pedrordgs/lttng_elasticsearch:latest