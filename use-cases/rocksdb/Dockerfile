FROM taniaesteves/rocksdb:v5.17.2 as rocksdb_image

FROM pedrordgs/lttng:latest
COPY --from=rocksdb_image /rocksdb /rocksdb

ENV ROCKSDB_DIRECTORY=/rocksdb

RUN apt-get update && apt-get install -y libgflags-dev libsnappy-dev zlib1g-dev libbz2-dev liblz4-dev libzstd-dev cmake time

WORKDIR /rocksdb

COPY entrypoint.sh ./start_db_bench.sh

ENTRYPOINT [ "/rocksdb/start_db_bench.sh" ]