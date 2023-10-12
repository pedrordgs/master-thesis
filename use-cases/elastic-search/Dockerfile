FROM pedrordgs/lttng:latest

RUN apt-get update && apt-get install -y openjdk-17-jdk wget

# Create a user 'elasticsearch' under 'elasticsearch'
RUN useradd -d /usr/share/elasticsearch -M -s /bin/bash -U elasticsearch

RUN wget https://artifacts.elastic.co/downloads/elasticsearch/elasticsearch-8.3.0-linux-x86_64.tar.gz && \ 
    tar -xzvf elasticsearch-8.3.0-linux-x86_64.tar.gz -C /usr/share/ && \
    rm elasticsearch-8.3.0-linux-x86_64.tar.gz

RUN chown -R elasticsearch:elasticsearch /usr/share/elasticsearch-8.3.0

WORKDIR /usr/share/elasticsearch-8.3.0

RUN echo "xpack.security.enabled: false" >> /usr/share/elasticsearch-8.3.0/config/elasticsearch.yml && \
    echo "discovery.type: single-node" >> /usr/share/elasticsearch-8.3.0/config/elasticsearch.yml

RUN sed -i 's/#network.host: 192.168.0.1/network.host: 0.0.0.0/g' /usr/share/elasticsearch-8.3.0/config/elasticsearch.yml

CMD ["runuser","-u","elasticsearch","--","bin/elasticsearch"]