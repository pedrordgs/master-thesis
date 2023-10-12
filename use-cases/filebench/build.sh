#!/bin/sh

docker build . -t pedrordgs/lttng_filebench:latest
docker push pedrordgs/lttng_filebench:latest