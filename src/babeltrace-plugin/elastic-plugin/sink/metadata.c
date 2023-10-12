#include "metadata.h"

// EventType, FuncType, Category
static const char *syscall_creat[3] = {"storage", "metadata", "FileManagement"};
static const char *syscall_open[3] = {"storage", "metadata", "FileManagement"};
static const char *syscall_openat[3] = {"storage", "metadata", "FileManagement"};
static const char *syscall_close[3] = {"storage", "metadata", "FileManagement"};
static const char *syscall_ftruncate[3] = {"storage", "metadata", "FileManagement"};
static const char *syscall_fsync[3] = {"storage", "data", "DeviceManagement"};
static const char *syscall_fdatasync[3] = {"storage", "data", "DeviceManagement"};
static const char *syscall_fstat[3] = {"storage", "metadata", "FileManagement"};
static const char *syscall_fstatfs[3] = {"storage", "metadata", "FileManagement"};
static const char *syscall_fgetxattr[3] = {"storage", "metadata", "InformationManagement"};
static const char *syscall_fsetxattr[3] = {"storage", "metadata", "InformationManagement"};
static const char *syscall_fremovexattr[3] = {"storage", "metadata", "InformationManagement"};
static const char *syscall_flistxattr[3] = {"storage", "metadata", "InformationManagement"};
static const char *syscall_listen[3] = {"network", "metadata", "Communication"};
static const char *syscall_rename[3] = {"storage", "metadata", "InformationManagement"};
static const char *syscall_renameat[3] = {"storage", "metadata", "InformationManagement"};
static const char *syscall_renameat2[3] = {"storage", "metadata", "InformationManagement"};
static const char *syscall_truncate[3] = {"storage", "metadata", "FileManagement"};
static const char *syscall_unlink[3] = {"storage", "metadata", "InformationManagement"};
static const char *syscall_unlinkat[3] = {"storage", "metadata", "InformationManagement"};
static const char *syscall_readlink[3] = {"storage", "metadata", "Other"};
static const char *syscall_stat[3] = {"storage", "metadata", "InformationManagement"};
static const char *syscall_fstatat[3] = {"storage", "metadata", "FileManagement"};
static const char *syscall_getxattr[3] = {"storage", "metadata", "InformationManagement"};
static const char *syscall_lgetxattr[3] = {"storage", "metadata", "InformationManagement"};
static const char *syscall_setxattr[3] = {"storage", "metadata", "InformationManagement"};
static const char *syscall_lsetxattr[3] = {"storage", "metadata", "InformationManagement"};
static const char *syscall_removexattr[3] = {"storage", "metadata", "InformationManagement"};
static const char *syscall_lremovexattr[3] = {"storage", "metadata", "InformationManagement"};
static const char *syscall_listxattr[3] = {"storage", "metadata", "InformationManagement"};
static const char *syscall_llistxattr[3] = {"storage", "metadata", "InformationManagement"};
static const char *syscall_mknod[3] = {"other", "metadata", "Other"};
static const char *syscall_mknodat[3] = {"other", "metadata", "Other"};
static const char *syscall_setrlimit[3] = {"other", "metadata", "InformationManagement"};
static const char *syscall_readahead[3] = {"storage", "data", "DeviceManagement"};
static const char *syscall_socket[3] = {"network", "metadata", "Communication"};
static const char *syscall_socketpair[3] = {"network", "metadata", "Communication"};
static const char *syscall_bind[3] = {"network", "metadata", "Communication"};
static const char *syscall_accept[3] = {"network", "metadata", "Communication"};
static const char *syscall_accept4[3] = {"network", "metadata", "Communication"};
static const char *syscall_connect[3] = {"network", "metadata", "Communication"};
static const char *syscall_getsockopt[3] = {"network", "metadata", "Communication"};
static const char *syscall_setsockopt[3] = {"network", "metadata", "Communication"};
static const char *syscall_read[3] = {"storage", "data", "FileManagement"};
static const char *syscall_pread[3] = {"storage", "data", "FileManagement"};
static const char *syscall_readv[3] = {"storage", "data", "FileManagement"};
static const char *syscall_write[3] = {"storage", "data", "FileManagement"};
static const char *syscall_pwrite[3] = {"storage", "data", "FileManagement"};
static const char *syscall_writev[3] = {"storage", "data", "FileManagement"};
static const char *syscall_recvfrom[3] = {"network", "data", "Communication"};
static const char *syscall_recvmsg[3] = {"network", "data", "Communication"};
static const char *syscall_sendto[3] = {"network", "data", "Communication"};
static const char *syscall_sendmsg[3] = {"network", "data", "Communication"};
static const char *syscall_lseek[3] = {"storage", "metadata", "FileManagement"};
static const char *syscall_readlinkat[3] = {"storage", "metadata", "Other"};

static const char **get_event_metadata(char *syscall_name) {
  if (strcmp(syscall_name, "creat") == 0)
    return syscall_creat;
  else if (strcmp(syscall_name, "open") == 0)
    return syscall_open;
  else if (strcmp(syscall_name, "openat") == 0)
    return syscall_openat;
  else if (strcmp(syscall_name, "close") == 0)
    return syscall_close;
  else if (strcmp(syscall_name, "ftruncate") == 0)
    return syscall_ftruncate;
  else if (strcmp(syscall_name, "fsync") == 0)
    return syscall_fsync;
  else if (strcmp(syscall_name, "fdatasync") == 0)
    return syscall_fdatasync;
  else if (strcmp(syscall_name, "newfstat") == 0)
    return syscall_fstat;
  else if (strcmp(syscall_name, "fstatfs") == 0)
    return syscall_fstatfs;
  else if (strcmp(syscall_name, "fgetxattr") == 0)
    return syscall_fgetxattr;
  else if (strcmp(syscall_name, "fsetxattr") == 0)
    return syscall_fsetxattr;
  else if (strcmp(syscall_name, "fremovexattr") == 0)
    return syscall_fremovexattr;
  else if (strcmp(syscall_name, "flistxattr") == 0)
    return syscall_flistxattr;
  else if (strcmp(syscall_name, "listen") == 0)
    return syscall_listen;
  else if (strcmp(syscall_name, "rename") == 0)
    return syscall_rename;
  else if (strcmp(syscall_name, "renameat") == 0)
    return syscall_renameat;
  else if (strcmp(syscall_name, "renameat2") == 0)
    return syscall_renameat2;
  else if (strcmp(syscall_name, "truncate") == 0)
    return syscall_truncate;
  else if (strcmp(syscall_name, "unlink") == 0)
    return syscall_unlink;
  else if (strcmp(syscall_name, "unlinkat") == 0)
    return syscall_unlinkat;
  else if (strcmp(syscall_name, "readlink") == 0)
    return syscall_readlink;
  else if (strcmp(syscall_name, "newstat") == 0)
    return syscall_stat;
  else if (strcmp(syscall_name, "newfstatat") == 0)
    return syscall_fstatat;
  else if (strcmp(syscall_name, "getxattr") == 0)
    return syscall_getxattr;
  else if (strcmp(syscall_name, "lgetxattr") == 0)
    return syscall_lgetxattr;
  else if (strcmp(syscall_name, "setxattr") == 0)
    return syscall_setxattr;
  else if (strcmp(syscall_name, "lsetxattr") == 0)
    return syscall_lsetxattr;
  else if (strcmp(syscall_name, "removexattr") == 0)
    return syscall_removexattr;
  else if (strcmp(syscall_name, "lremovexattr") == 0)
    return syscall_lremovexattr;
  else if (strcmp(syscall_name, "listxattr") == 0)
    return syscall_listxattr;
  else if (strcmp(syscall_name, "llistxattr") == 0)
    return syscall_llistxattr;
  else if (strcmp(syscall_name, "mknod") == 0)
    return syscall_mknod;
  else if (strcmp(syscall_name, "mknodat") == 0)
    return syscall_mknodat;
  else if (strcmp(syscall_name, "setrlimit") == 0)
    return syscall_setrlimit;
  else if (strcmp(syscall_name, "readahead") == 0)
    return syscall_readahead;
  else if (strcmp(syscall_name, "socket") == 0)
    return syscall_socket;
  else if (strcmp(syscall_name, "socketpair") == 0)
    return syscall_socketpair;
  else if (strcmp(syscall_name, "bind") == 0)
    return syscall_bind;
  else if (strcmp(syscall_name, "accept") == 0)
    return syscall_accept;
  else if (strcmp(syscall_name, "accept4") == 0)
    return syscall_accept4;
  else if (strcmp(syscall_name, "connect") == 0)
    return syscall_connect;
  else if (strcmp(syscall_name, "getsockopt") == 0)
    return syscall_getsockopt;
  else if (strcmp(syscall_name, "setsockopt") == 0)
    return syscall_setsockopt;
  else if (strcmp(syscall_name, "read") == 0)
    return syscall_read;
  else if (strcmp(syscall_name, "pread64") == 0)
    return syscall_pread;
  else if (strcmp(syscall_name, "readv") == 0)
    return syscall_readv;
  else if (strcmp(syscall_name, "write") == 0)
    return syscall_write;
  else if (strcmp(syscall_name, "pwrite64") == 0)
    return syscall_pwrite;
  else if (strcmp(syscall_name, "writev") == 0)
    return syscall_writev;
  else if (strcmp(syscall_name, "recvfrom") == 0)
    return syscall_recvfrom;
  else if (strcmp(syscall_name, "recvmsg") == 0)
    return syscall_recvmsg;
  else if (strcmp(syscall_name, "sendto") == 0)
    return syscall_sendto;
  else if (strcmp(syscall_name, "sendmsg") == 0)
    return syscall_sendmsg;
  else if (strcmp(syscall_name, "lseek") == 0)
    return syscall_lseek;
  else if (strcmp(syscall_name, "readlinkat") == 0) {
    return syscall_readlinkat;
  }
  return NULL;
}

const char *get_metadata_event_type(char *syscall_name) {
  if (!syscall_name)
    return NULL;
  const char **metadata = get_event_metadata(syscall_name);
  if (!metadata) {
    printf("[WARNING] Metadata not defined for system call %s\n", syscall_name);
    return "";
  }
  return metadata[0];
}

const char *get_metadata_func_type(char *syscall_name) {
  if (!syscall_name)
    return NULL;
  const char **metadata = get_event_metadata(syscall_name);
  if (!metadata) {
    printf("[WARNING] Metadata not defined for system call %s\n", syscall_name);
    return "";
  }
  return metadata[1];
}

const char *get_metadata_category(char *syscall_name) {
  if (!syscall_name)
    return NULL;
  const char **metadata = get_event_metadata(syscall_name);
  if (!metadata) {
    printf("[WARNING] Metadata not defined for system call %s\n", syscall_name);
    return "";
  }
  return metadata[2];
}