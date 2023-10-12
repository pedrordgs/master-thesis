# LTTng Trace

Wrapper around `LTTng` so you can run it against an executable command, just like `strace`.

## Table of Contents
- [LTTng Trace](#lttng-trace)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Components](#components)
    - [lttng-noty](#lttng-noty)
    - [lttng-trace](#lttng-trace-1)
  - [Usage](#usage)
  - [Contributing](#contributing)
  - [License](#license)

## Introduction

The [LTTng (Linux Trace Toolkit: next generation)](https://lttng.org/) project is designed to provide efficient and comprehensive tracing on Linux systems. It offers a powerful framework for collecting trace data from the kernel and user-space applications. 

This project allows you to run `LTTng` against an executable command. In order to do that, this repository encompasses two key components: `lttng-noty` and `lttng-trace`.

## Components

### lttng-noty

`lttng-noty` is a notification service that activate tracing againts the PID of the child process when a fork occurs.

### lttng-trace

`lttng-trace` is the core component, responsible for running the received command and activate `LTTng` on that command.

## Usage

You can use it by running a container with `pedrordgs/lttng:latest` image, like this:

```bash
docker run -it --name lttng_trace --pid=host --privileged --cap-add=ALL --net=host -v /lib/modules:/lib/modules -v /usr/src:/usr/src -v /sys/kernel/debug/:/sys/kernel/debug/ -e LTTNG_SESSION_NAME=<session-name> -e LTTNG_SYSCALLS='open;close;creat;read;write' -e LTTNG_EXTRA_CONTEXT='pid;tid;hostname;procname;ppid' pedrordgs/lttng:latest <command>
```

## Contributing

We welcome contributions to improve this components and its documentation. Feel free to submit issues and pull requests on our [GitHub repository](https://github.com/pedrordgs/master-thesis/).

## License

This project is licensed under the MIT License - see the [LICENSE](../../LICENSE) file for details.

---

For more details on using LTTng, please refer to the official [LTTng documentation](https://lttng.org/docs/v2.13/).

Happy tracing! 🚀