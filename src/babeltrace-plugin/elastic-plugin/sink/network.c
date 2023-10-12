#include "network.h"

const char *get_address_family_name(int64_t address_family) {
  switch (address_family) {
  case AF_UNSPEC:
    return "AF_UNSPEC";
  case AF_UNIX:
    return "AF_UNIX";
  case AF_INET:
    return "AF_INET";
  case AF_AX25:
    return "AF_AX25";
  case AF_IPX:
    return "AF_IPX";
  case AF_APPLETALK:
    return "AF_APPLETALK";
  case AF_NETROM:
    return "AF_NETROM";
  case AF_BRIDGE:
    return "AF_BRIDGE";
  case AF_ATMPVC:
    return "AF_ATMPVC";
  case AF_X25:
    return "AF_X25";
  case AF_INET6:
    return "AF_INET6";
  case AF_ROSE:
    return "AF_ROSE";
  case AF_DECnet:
    return "AF_DECnet";
  case AF_NETBEUI:
    return "AF_NETBEUI";
  case AF_SECURITY:
    return "AF_SECURITY";
  case AF_KEY:
    return "AF_KEY";
  case AF_NETLINK:
    return "AF_NETLINK";
  case AF_PACKET:
    return "AF_PACKET";
  case AF_ASH:
    return "AF_ASH";
  case AF_ECONET:
    return "AF_ECONET";
  case AF_ATMSVC:
    return "AF_ATMSVC";
  case AF_RDS:
    return "AF_RDS";
  case AF_SNA:
    return "AF_SNA";
  case AF_IRDA:
    return "AF_IRDA";
  case AF_PPPOX:
    return "AF_PPPOX";
  case AF_WANPIPE:
    return "AF_WANPIPE";
  case AF_LLC:
    return "AF_LLC";
  case AF_IB:
    return "AF_IB";
  case AF_MPLS:
    return "AF_MPLS";
  case AF_CAN:
    return "AF_CAN";
  case AF_TIPC:
    return "AF_TIPC";
  case AF_BLUETOOTH:
    return "AF_BLUETOOTH";
  case AF_IUCV:
    return "AF_IUCV";
  case AF_RXRPC:
    return "AF_RXRPC";
  case AF_ISDN:
    return "AF_ISDN";
  case AF_PHONET:
    return "AF_PHONET";
  case AF_IEEE802154:
    return "AF_IEEE802154";
  case AF_CAIF:
    return "AF_CAIF";
  case AF_ALG:
    return "AF_ALG";
  case AF_NFC:
    return "AF_NFC";
  case AF_VSOCK:
    return "AF_VSOCK";
  case AF_KCM:
    return "AF_KCM";
  case AF_QIPCRTR:
    return "AF_QIPCRTR";
  case AF_SMC:
    return "AF_SMC";
  default:
  }
  return g_strdup_printf("%ld", address_family);
}

static char *get_socket_optname(int64_t optname) {
  switch (optname) {
  case SO_DEBUG:
    return "SO_DEBUG";
  case SO_REUSEADDR:
    return "SO_REUSEADDR";
  case SO_KEEPALIVE:
    return "SO_KEEPALIVE";
  case SO_DONTROUTE:
    return "SO_DONTROUTE";
  case SO_BROADCAST:
    return "SO_BROADCAST";
  case SO_LINGER:
    return "SO_LINGER";
  case SO_OOBINLINE:
    return "SO_OOBINLINE";
  case SO_REUSEPORT:
    return "SO_REUSEPORT";
  case SO_TYPE:
    return "SO_TYPE";
  case SO_ERROR:
    return "SO_ERROR";
  case SO_SNDBUF:
    return "SO_SNDBUF";
  case SO_RCVBUF:
    return "SO_RCVBUF";
  case SO_SNDBUFFORCE:
    return "SO_SNDBUFFORCE";
  case SO_RCVBUFFORCE:
    return "SO_RCVBUFFORCE";
  case SO_RCVLOWAT:
    return "SO_RCVLOWAT";
  case SO_SNDLOWAT:
    return "SO_SNDLOWAT";
  case SO_RCVTIMEO_OLD:
    return "SO_RCVTIMEO_OLD";
  case SO_SNDTIMEO_OLD:
    return "SO_SNDTIMEO_OLD";
  case SO_ACCEPTCONN:
    return "SO_ACCEPTCONN";
  case SO_PROTOCOL:
    return "SO_PROTOCOL";
  case SO_DOMAIN:
    return "SO_DOMAIN";
  case SO_NO_CHECK:
    return "SO_NO_CHECK";
  case SO_PRIORITY:
    return "SO_PRIORITY";
  case SO_BSDCOMPAT:
    return "SO_BSDCOMPAT";
  case SO_PASSCRED:
    return "SO_PASSCRED";
  case SO_PEERCRED:
    return "SO_PEERCRED";
  case SO_BINDTODEVICE:
    return "SO_BINDTODEVICE";
  case SO_ATTACH_FILTER:
    return "SO_ATTACH_FILTER";
  case SO_DETACH_FILTER:
    return "SO_DETACH_FILTER";
  case SO_PEERNAME:
    return "SO_PEERNAME";
  case SO_PEERSEC:
    return "SO_PEERSEC";
  case SO_PASSSEC:
    return "SO_PASSSEC";
  case SO_SECURITY_AUTHENTICATION:
    return "SO_SECURITY_AUTHENTICATION";
  case SO_SECURITY_ENCRYPTION_TRANSPORT:
    return "SO_SECURITY_ENCRYPTION_TRANSPORT";
  case SO_SECURITY_ENCRYPTION_NETWORK:
    return "SO_SECURITY_ENCRYPTION_NETWORK";
  case SO_MARK:
    return "SO_MARK";
  case SO_RXQ_OVFL:
    return "SO_RXQ_OVFL";
  case SO_WIFI_STATUS:
    return "SO_WIFI_STATUS";
  case SO_PEEK_OFF:
    return "SO_PEEK_OFF";
  case SO_NOFCS:
    return "SO_NOFCS";
  case SO_LOCK_FILTER:
    return "SO_LOCK_FILTER";
  case SO_SELECT_ERR_QUEUE:
    return "SO_SELECT_ERR_QUEUE";
  case SO_BUSY_POLL:
    return "SO_BUSY_POLL";
  case SO_MAX_PACING_RATE:
    return "SO_MAX_PACING_RATE";
  case SO_BPF_EXTENSIONS:
    return "SO_BPF_EXTENSIONS";
  case SO_INCOMING_CPU:
    return "SO_INCOMING_CPU";
  case SO_ATTACH_BPF:
    return "SO_ATTACH_BPF";
  case SO_ATTACH_REUSEPORT_CBPF:
    return "SO_ATTACH_REUSEPORT_CBPF";
  case SO_ATTACH_REUSEPORT_EBPF:
    return "SO_ATTACH_REUSEPORT_EBPF";
  case SO_CNX_ADVICE:
    return "SO_CNX_ADVICE";
  case SCM_TIMESTAMPING_OPT_STATS:
    return "SCM_TIMESTAMPING_OPT_STATS";
  case SO_MEMINFO:
    return "SO_MEMINFO";
  case SO_INCOMING_NAPI_ID:
    return "SO_INCOMING_NAPI_ID";
  case SO_COOKIE:
    return "SO_COOKIE";
  case SCM_TIMESTAMPING_PKTINFO:
    return "SCM_TIMESTAMPING_PKTINFO";
  case SO_PEERGROUPS:
    return "SO_PEERGROUPS";
  case SO_ZEROCOPY:
    return "SO_ZEROCOPY";
  case SO_TXTIME:
    return "SO_TXTIME";
  case SO_BINDTOIFINDEX:
    return "SO_BINDTOIFINDEX";
  case SO_TIMESTAMP_OLD:
    return "SO_TIMESTAMP_OLD";
  case SO_TIMESTAMPNS_OLD:
    return "SO_TIMESTAMPNS_OLD";
  case SO_TIMESTAMPING_OLD:
    return "SO_TIMESTAMPING_OLD";
  case SO_TIMESTAMP_NEW:
    return "SO_TIMESTAMP_NEW";
  case SO_TIMESTAMPNS_NEW:
    return "SO_TIMESTAMPNS_NEW";
  case SO_TIMESTAMPING_NEW:
    return "SO_TIMESTAMPING_NEW";
  case SO_RCVTIMEO_NEW:
    return "SO_RCVTIMEO_NEW";
  case SO_SNDTIMEO_NEW:
    return "SO_SNDTIMEO_NEW";
  case SO_DETACH_REUSEPORT_BPF:
    return "SO_DETACH_REUSEPORT_BPF";
  default:
  }
  return g_strdup_printf("%ld", optname);
}

static char *get_ip_optname(int64_t optname) {
  switch (optname) {
  case IP_TOS:
    return "IP_TOS";
  case IP_TTL:
    return "IP_TTL";
  case IP_HDRINCL:
    return "IP_HDRINCL";
  case IP_OPTIONS:
    return "IP_OPTIONS";
  case IP_ROUTER_ALERT:
    return "IP_ROUTER_ALERT";
  case IP_RECVOPTS:
    return "IP_RECVOPTS";
  case IP_RETOPTS:
    return "IP_RETOPTS";
  case IP_PKTINFO:
    return "IP_PKTINFO";
  case IP_PKTOPTIONS:
    return "IP_PKTOPTIONS";
  case IP_MTU_DISCOVER:
    return "IP_MTU_DISCOVER";
  case IP_RECVERR:
    return "IP_RECVERR";
  case IP_RECVTTL:
    return "IP_RECVTTL";
  case IP_RECVTOS:
    return "IP_RECVTOS";
  case IP_MTU:
    return "IP_MTU";
  case IP_FREEBIND:
    return "IP_FREEBIND";
  case IP_IPSEC_POLICY:
    return "IP_IPSEC_POLICY";
  case IP_XFRM_POLICY:
    return "IP_XFRM_POLICY";
  case IP_PASSSEC:
    return "IP_PASSSEC";
  case IP_TRANSPARENT:
    return "IP_TRANSPARENT";
  case IP_ORIGDSTADDR:
    return "IP_ORIGDSTADDR";
  case IP_MINTTL:
    return "IP_MINTTL";
  case IP_NODEFRAG:
    return "IP_NODEFRAG";
  case IP_CHECKSUM:
    return "IP_CHECKSUM";
  case IP_BIND_ADDRESS_NO_PORT:
    return "IP_BIND_ADDRESS_NO_PORT";
  case IP_RECVFRAGSIZE:
    return "IP_RECVFRAGSIZE";
  case IP_PMTUDISC_DONT:
    return "IP_PMTUDISC_DONT";
  case IP_MULTICAST_IF:
    return "IP_MULTICAST_IF";
  case IP_MULTICAST_TTL:
    return "IP_MULTICAST_TTL";
  case IP_MULTICAST_LOOP:
    return "IP_MULTICAST_LOOP";
  case IP_ADD_MEMBERSHIP:
    return "IP_ADD_MEMBERSHIP";
  case IP_DROP_MEMBERSHIP:
    return "IP_DROP_MEMBERSHIP";
  case IP_UNBLOCK_SOURCE:
    return "IP_UNBLOCK_SOURCE";
  case IP_BLOCK_SOURCE:
    return "IP_BLOCK_SOURCE";
  case IP_ADD_SOURCE_MEMBERSHIP:
    return "IP_ADD_SOURCE_MEMBERSHIP";
  case IP_DROP_SOURCE_MEMBERSHIP:
    return "IP_DROP_SOURCE_MEMBERSHIP";
  case IP_MSFILTER:
    return "IP_MSFILTER";
  case MCAST_JOIN_GROUP:
    return "MCAST_JOIN_GROUP";
  case MCAST_BLOCK_SOURCE:
    return "MCAST_BLOCK_SOURCE";
  case MCAST_UNBLOCK_SOURCE:
    return "MCAST_UNBLOCK_SOURCE";
  case MCAST_LEAVE_GROUP:
    return "MCAST_LEAVE_GROUP";
  case MCAST_JOIN_SOURCE_GROUP:
    return "MCAST_JOIN_SOURCE_GROUP";
  case MCAST_LEAVE_SOURCE_GROUP:
    return "MCAST_LEAVE_SOURCE_GROUP";
  case MCAST_MSFILTER:
    return "MCAST_MSFILTER";
  case IP_MULTICAST_ALL:
    return "IP_MULTICAST_ALL";
  case IP_UNICAST_IF:
    return "IP_UNICAST_IF";
  default:
  }
  return g_strdup_printf("%ld", optname);
}

static char *get_tcp_optname(int64_t optname) {
  switch (optname) {
  case TCP_NODELAY:
    return "TCP_NODELAY";
  case TCP_MAXSEG:
    return "TCP_MAXSEG";
  case TCP_CORK:
    return "TCP_CORK";
  case TCP_KEEPIDLE:
    return "TCP_KEEPIDLE";
  case TCP_KEEPINTVL:
    return "TCP_KEEPINTVL";
  case TCP_KEEPCNT:
    return "TCP_KEEPCNT";
  case TCP_SYNCNT:
    return "TCP_SYNCNT";
  case TCP_LINGER2:
    return "TCP_LINGER2";
  case TCP_DEFER_ACCEPT:
    return "TCP_DEFER_ACCEPT";
  case TCP_WINDOW_CLAMP:
    return "TCP_WINDOW_CLAMP";
  case TCP_INFO:
    return "TCP_INFO";
  case TCP_QUICKACK:
    return "TCP_QUICKACK";
  case TCP_CONGESTION:
    return "TCP_CONGESTION";
  case TCP_MD5SIG:
    return "TCP_MD5SIG";
  case TCP_THIN_LINEAR_TIMEOUTS:
    return "TCP_THIN_LINEAR_TIMEOUTS";
  case TCP_THIN_DUPACK:
    return "TCP_THIN_DUPACK";
  case TCP_USER_TIMEOUT:
    return "TCP_USER_TIMEOUT";
  case TCP_REPAIR:
    return "TCP_REPAIR";
  case TCP_REPAIR_QUEUE:
    return "TCP_REPAIR_QUEUE";
  case TCP_QUEUE_SEQ:
    return "TCP_QUEUE_SEQ";
  case TCP_REPAIR_OPTIONS:
    return "TCP_REPAIR_OPTIONS";
  case TCP_FASTOPEN:
    return "TCP_FASTOPEN";
  case TCP_TIMESTAMP:
    return "TCP_TIMESTAMP";
  case TCP_NOTSENT_LOWAT:
    return "TCP_NOTSENT_LOWAT";
  case TCP_CC_INFO:
    return "TCP_CC_INFO";
  case TCP_SAVE_SYN:
    return "TCP_SAVE_SYN";
  case TCP_SAVED_SYN:
    return "TCP_SAVED_SYN";
  case TCP_REPAIR_WINDOW:
    return "TCP_REPAIR_WINDOW";
  case TCP_FASTOPEN_CONNECT:
    return "TCP_FASTOPEN_CONNECT";
  case TCP_ULP:
    return "TCP_ULP";
  case TCP_MD5SIG_EXT:
    return "TCP_MD5SIG_EXT";
  case TCP_FASTOPEN_KEY:
    return "TCP_FASTOPEN_KEY";
  case TCP_FASTOPEN_NO_COOKIE:
    return "TCP_FASTOPEN_NO_COOKIE";
  case TCP_ZEROCOPY_RECEIVE:
    return "TCP_ZEROCOPY_RECEIVE";
  case TCP_INQ:
    return "TCP_INQ";
  case TCP_TX_DELAY:
    return "TCP_TX_DELAY";
  default:
  }
  return g_strdup_printf("%ld", optname);
}

void get_level_optname_name(int64_t level, int64_t optname, char *ret[]) {
  switch (level) {
  case SOL_SOCKET:
    ret[0] = "SOL_SOCKET";
    ret[1] = get_socket_optname(optname);
    break;
  case IPPROTO_IP:
    ret[0] = "IPPROTO_IP";
    ret[1] = get_ip_optname(optname);
    break;
  case IPPROTO_TCP:
    ret[0] = "IPPROTO_TCP";
    ret[1] = get_tcp_optname(optname);
    break;
  default:
    ret[0] = g_strdup_printf("%ld", level);
    ret[1] = g_strdup_printf("%ld", optname);
  }
}

const char *get_socket_type(int64_t socket_type) {
  switch (socket_type) {
  case SOCK_STREAM:
    return "SOCK_STREAM";
  case SOCK_DGRAM:
    return "SOCK_DGRAM";
  case SOCK_RAW:
    return "SOCK_RAW";
  case SOCK_RDM:
    return "SOCK_RDM";
  case SOCK_SEQPACKET:
    return "SOCK_SEQPACKET";
  case SOCK_PACKET:
    return "SOCK_PACKET";
  case SOCK_DCCP:
    return "SOCK_DCCP";
  default:
  }
  return g_strdup_printf("%ld", socket_type);
}

static const char *get_ipp_protocol(int64_t protocol) {
  switch (protocol) {
  case IPPROTO_IP:
    return "IPPROTO_IP";
  case IPPROTO_ICMP:
    return "IPPROTO_ICMP";
  case IPPROTO_IGMP:
    return "IPPROTO_IGMP";
  case IPPROTO_IPIP:
    return "IPPROTO_IPIP";
  case IPPROTO_TCP:
    return "IPPROTO_TCP";
  case IPPROTO_EGP:
    return "IPPROTO_EGP";
  case IPPROTO_PUP:
    return "IPPROTO_PUP";
  case IPPROTO_UDP:
    return "IPPROTO_UDP";
  case IPPROTO_IDP:
    return "IPPROTO_IDP";
  case IPPROTO_TP:
    return "IPPROTO_TP";
  case IPPROTO_DCCP:
    return "IPPROTO_DCCP";
  case IPPROTO_IPV6:
    return "IPPROTO_IPV6";
  case IPPROTO_RSVP:
    return "IPPROTO_RSVP";
  case IPPROTO_GRE:
    return "IPPROTO_GRE";
  case IPPROTO_ESP:
    return "IPPROTO_ESP";
  case IPPROTO_AH:
    return "IPPROTO_AH";
  case IPPROTO_MTP:
    return "IPPROTO_MTP";
  case IPPROTO_BEETPH:
    return "IPPROTO_BEETPH";
  case IPPROTO_ENCAP:
    return "IPPROTO_ENCAP";
  case IPPROTO_PIM:
    return "IPPROTO_PIM";
  case IPPROTO_COMP:
    return "IPPROTO_COMP";
  case IPPROTO_SCTP:
    return "IPPROTO_SCTP";
  case IPPROTO_UDPLITE:
    return "IPPROTO_UDPLITE";
  case IPPROTO_MPLS:
    return "IPPROTO_MPLS";
  case IPPROTO_RAW:
    return "IPPROTO_RAW";
  case IPPROTO_MAX:
    return "IPPROTO_MAX";
  default:
  }
  return g_strdup_printf("%ld", protocol);
}

static const char *get_netlink_protocol(int64_t protocol) {
  switch (protocol) {
  case NETLINK_ROUTE:
    return "NETLINK_ROUTE";
  case NETLINK_UNUSED:
    return "NETLINK_UNUSED";
  case NETLINK_USERSOCK:
    return "NETLINK_USERSOCK";
  case NETLINK_FIREWALL:
    return "NETLINK_FIREWALL";
  case NETLINK_SOCK_DIAG:
    return "NETLINK_SOCK_DIAG";
  case NETLINK_NFLOG:
    return "NETLINK_NFLOG";
  case NETLINK_XFRM:
    return "NETLINK_XFRM";
  case NETLINK_SELINUX:
    return "NETLINK_SELINUX";
  case NETLINK_ISCSI:
    return "NETLINK_ISCSI";
  case NETLINK_AUDIT:
    return "NETLINK_AUDIT";
  case NETLINK_FIB_LOOKUP:
    return "NETLINK_FIB_LOOKUP";
  case NETLINK_CONNECTOR:
    return "NETLINK_CONNECTOR";
  case NETLINK_NETFILTER:
    return "NETLINK_NETFILTER";
  case NETLINK_IP6_FW:
    return "NETLINK_IP6_FW";
  case NETLINK_DNRTMSG:
    return "NETLINK_DNRTMSG";
  case NETLINK_KOBJECT_UEVENT:
    return "NETLINK_KOBJECT_UEVENT";
  case NETLINK_GENERIC:
    return "NETLINK_GENERIC";
  case NETLINK_SCSITRANSPORT:
    return "NETLINK_SCSITRANSPORT";
  case NETLINK_ECRYPTFS:
    return "NETLINK_ECRYPTFS";
  case NETLINK_RDMA:
    return "NETLINK_RDMA";
  case NETLINK_CRYPTO:
    return "NETLINK_CRYPTO";
  case NETLINK_SMC:
    return "NETLINK_SM";
  default:
  }
  return g_strdup_printf("%ld", protocol);
}

const char *get_protocol_name(int64_t family, int64_t protocol) {
  switch (family) {
  case AF_INET:
  case AF_INET6:
    return get_ipp_protocol(protocol);
  case AF_NETLINK:
    return get_netlink_protocol(protocol);
  default:
  }
  return g_strdup_printf("%ld", protocol);
}