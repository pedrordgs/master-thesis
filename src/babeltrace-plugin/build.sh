#!/bin/sh

docker build . -t pedrordgs/babeltrace:latest
docker push pedrordgs/babeltrace:latest