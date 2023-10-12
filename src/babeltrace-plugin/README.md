# Babeltrace2 Elasticsearch Plugin

This is a Babeltrace2 plugin designed to send trace data to Elasticsearch for real-time analysis and visualization.

## Table of Contents
- [Babeltrace2 Elasticsearch Plugin](#babeltrace2-elasticsearch-plugin)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Usage](#usage)
  - [Contributing](#contributing)
  - [License](#license)

## Introduction

[Babeltrace2](https://babeltrace.org/) is a versatile trace processing framework that allows you to analyze and convert trace data from various sources and formats. This plugin extends Babeltrace2's functionality to enable direct integration with Elasticsearch, a popular real-time data storage and analysis platform.

The primary purpose of this plugin is to facilitate the seamless transfer of trace data to Elasticsearch, enabling real-time monitoring, analysis, and visualization of system and application traces.

## Usage

You can use it by running a container with `pedrordgs/babeltrace:latest` image, like this:

```bash
docker run -it --name parser --net=host -e ES_ADDRESSES=<elasticsearch-address> -e ES_USER=<elasticsearch-user> -e ES_PWD=<elasticsearch-password> -e ES_INDEX_NAME=<elasticsearch-index> -e LTTNG_ADDRESS=<tracer-address> -e pedrordgs/babeltrace:latest
```

## Contributing

We welcome contributions to improve this plugin and its documentation. Feel free to submit issues and pull requests on our [GitHub repository]().

## License

This project is licensed under the MIT License - see the [LICENSE]() file for details.

---

For more details on using Babeltrace2, please refer to the official [Babeltrace2 documentation](https://babeltrace.org/).

Happy tracing and analysis! 🚀