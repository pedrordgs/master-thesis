FROM ubuntu:22.04

# Create LTTng installation folder
RUN mkdir -p /usr/share/babeltrace2/elastic-plugin /docker/
WORKDIR /usr/share/babeltrace2/

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Lisbon

# Install dependencies
RUN apt-get update -y && \
    apt-get install -y wget git time && \
    apt-get install -y make automake autoconf libtool flex bison && \
    apt-get install -y libelf-dev libdw-dev libbabeltrace2-0 && \
    apt-get install -y libglib2.0-dev libjson-c-dev 

# Install GO-1.17.4
RUN wget https://go.dev/dl/go1.17.4.linux-amd64.tar.gz && \
    tar -xzf go1.17.4.linux-amd64.tar.gz && rm go1.17.4.linux-amd64.tar.gz

# Add go path to PATH ENV
ENV PATH=$PATH:/usr/share/babeltrace2/go/bin

# Install babeltrace2
RUN git clone https://github.com/efficios/babeltrace.git -b stable-2.0 && \
    cd babeltrace && \
    ./bootstrap && \
    ./configure --enable-debug-info --disable-man-pages && \
    make && \
    make install


COPY elastic-plugin /usr/share/babeltrace2/elastic-plugin/

# Install elastic-plugin
WORKDIR /usr/share/babeltrace2/elastic-plugin
RUN ./install.sh

COPY docker /docker/

CMD ["/docker/entrypoint.sh" ]