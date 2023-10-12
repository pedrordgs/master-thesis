#ifndef ELASTIC_METADATA_H
#define ELASTIC_METADATA_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *get_metadata_event_type(char *syscall_name);
const char *get_metadata_func_type(char *syscall_name);
const char *get_metadata_category(char *syscall_name);

#endif
