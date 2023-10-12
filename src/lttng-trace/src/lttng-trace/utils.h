#ifndef UTILS_H
#define UTILS_H

#include <lttng/lttng.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <glib.h>

char* get_session_stats_str(const char *session_name);

#endif