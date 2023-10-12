# Master Thesis

Analysis of I/O patterns for data management systems.

## Table of Contents
- [Master Thesis](#master-thesis)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Components](#components)
    - [Babeltrace Plugin](#babeltrace-plugin)
    - [LTTng Trace](#lttng-trace)
  - [Usage](#usage)
  - [License](#license)

## Introduction

This project is dedicated to exploring and enhancing Linux tracing and analysis capabilities. This repository houses two essential components: the Babeltrace Plugin and the LTTng Trace. These components are crucial for trace data processing, analysis, and real-time insights.

## Components

### Babeltrace Plugin

- [Babeltrace Plugin](./src/babeltrace-plugin) is an essential component for processing and sending trace data to Elasticsearch using the [Babeltrace2](https://babeltrace.org/) framework.

### LTTng Trace

- [LTTng Trace](./src/lttng-trace) is essential to allow us to run [LTTng](https://lttng.org/) over a specific command.

## Usage

For detailed usage instructions and examples, please refer to the documentation of each component:

- [Babeltrace Plugin Documentation](./src/babeltrace-plugin/README.md)
- [LTTng Documentation](./src/lttng-trace/README.md)


## License

This project is licensed under the MIT License - see the [LICENSE]() file for details.

---

Happy tracing and analysis! 🚀