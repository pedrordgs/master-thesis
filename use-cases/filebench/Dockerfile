FROM pedrordgs/lttng:latest

# Install filebench

RUN mkdir -p /filebench
WORKDIR /filebench

RUN apt-get update && \
    apt-get install -y software-properties-common && \
    apt-get install -y wget python3 python3-pip

RUN git clone https://github.com/filebench/filebench.git && \
    cd filebench && \
    git checkout 22620e6 && \
    libtoolize && \
    aclocal && \
    autoheader && \
    automake --add-missing && \
    autoconf && \
    ./configure && \
    make && \
    make install

COPY entrypoint.sh /filebench/

ENTRYPOINT [ "/filebench/entrypoint.sh" ]
CMD ["filebench","-f","/filebench/workloads/fileserver.f"]