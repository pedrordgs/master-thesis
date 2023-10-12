#ifndef ELASTIC_STORAGE_H
#define ELASTIC_STORAGE_H

#define _GNU_SOURCE

#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glib.h>

const char *get_open_flags(int64_t flags);
const char *get_creation_mode(int64_t flags, int64_t mode);

#endif
