#!/bin/sh

docker build . -t pedrordgs/lttng:latest
docker push pedrordgs/lttng:latest