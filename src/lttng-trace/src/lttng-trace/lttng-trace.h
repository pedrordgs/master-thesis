#ifndef LTTNG_TRACE_H
#define LTTNG_TRACE_H

#include <assert.h>
#include <glib.h>
#include <lttng/lttng.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "utils.h"

#define LTTNG_EVENT_FILTER "$ctx.procname != 'lttng*'"

#define PROCESS_FORK_TRIGGER_NAME "process-fork"
#define PROCESS_FORK_TRIGGER_PATTERN "sched_process_fork"

struct opts {
  char *session_name;
  GPtrArray *syscalls;
  GPtrArray *tracepoints;
  GPtrArray *ctx_types;
  char *exec_command;
  char *filter_tid;
};

#endif