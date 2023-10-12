#!/bin/sh

BASE_DIR=$(pwd)
ELASTIC_CLIENT_DIR=$BASE_DIR/sink/elastic-client

cd $ELASTIC_CLIENT_DIR
make

cd $BASE_DIR
make