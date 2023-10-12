FROM ubuntu:22.04

# Create LTTng installation folder
RUN mkdir -p /usr/share/lttng-tracer /usr/share/lttng-tracer/tools /lttng_trace_data
WORKDIR /usr/share/lttng-tracer/tools

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Lisbon

# Install dependencies
RUN apt-get update -y && \
    apt-get install -y liburcu-dev libpopt-dev libxml2-dev git kmod && \
    apt-get install -y make automake autoconf libtool pkg-config flex bison && \
    apt-get install -y libnuma-dev libglib2.0-dev

# Install LTTng UST
RUN git clone https://github.com/lttng/lttng-ust.git && \
    cd lttng-ust && \
    git checkout stable-2.13 && \
    ./bootstrap && \
    ./configure --disable-man-pages && \
    make && \
    make install && \
    ldconfig

# Install LTTng tools
RUN git clone https://github.com/lttng/lttng-tools.git && \
    cd lttng-tools && \
    git checkout stable-2.13 && \
    ./bootstrap && \
    ./configure --disable-man-pages && \
    make && \
    make install && \
    ldconfig

# Install lttng libs
COPY src /usr/share/lttng-tracer/

WORKDIR /usr/share/lttng-tracer/
RUN cd lttng-noty && make install
RUN cd lttng-trace && make install

COPY docker/entrypoint.sh /usr/share/lttng-tracer/
COPY docker/filter_tids_endpoint.sh /usr/share/lttng-tracer/

ENTRYPOINT ["/usr/share/lttng-tracer/entrypoint.sh"]