#ifndef ELASTIC_NETWORK_H
#define ELASTIC_NETWORK_H

#include <inttypes.h>
#include <linux/netlink.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glib.h>

const char *get_address_family_name(int64_t address_family);
void get_level_optname_name(int64_t level, int64_t optname, char *ret[]);
const char *get_socket_type(int64_t socket_type);
const char *get_protocol_name(int64_t family, int64_t protocol);

#endif
