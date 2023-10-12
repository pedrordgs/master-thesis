#include "storage.h"

static const char *get_open_flag_name(int flag) {
  switch (flag) {
  case O_RDONLY:
    return "O_RDONLY";
  case O_WRONLY:
    return "O_WRONLY";
  case O_RDWR:
    return "O_RDWR";
  case O_CREAT:
    return "O_CREAT";
  case O_EXCL:
    return "O_EXCL";
  case O_NOCTTY:
    return "O_NOCTTY";
  case O_TRUNC:
    return "O_TRUNC";
  case O_APPEND:
    return "O_APPEND";
  case O_NONBLOCK:
    return "O_NONBLOCK";
  case O_SYNC:
    return "O_SYNC";
  case O_DSYNC:
    return "O_DSYNC";
  case O_DIRECT:
    return "O_DIRECT";
  case O_NOFOLLOW:
    return "O_NOFOLLOW";
  case O_NOATIME:
    return "O_NOATIME";
  case O_CLOEXEC:
    return "O_CLOEXEC";
  case O_PATH:
    return "O_PATH";
  case O_TMPFILE:
    return "O_TMPFILE";
  case O_DIRECTORY:
    return "O_DIRECTORY";
  case O_ASYNC:
    return "O_ASYNC";
  default:
  }
  return g_strdup_printf("%d", flag);
}

const char *get_open_flags(int64_t flags) {
  char *ret = NULL;
  int file_access_flags[3] = {O_RDONLY, O_WRONLY, O_RDWR};
  for (int i = 0; i < 3; i++) {
    if ((flags & O_ACCMODE) == file_access_flags[i]) {
      flags = flags & ~O_ACCMODE;
      if (!ret) {
        ret = g_strdup_printf("%s", get_open_flag_name(file_access_flags[i]));
      } else {
        ret = g_strdup_printf("%s|%s", ret, get_open_flag_name(file_access_flags[i]));
      }
      break;
    }
  }
  int file_flags[16] = {
      O_CREAT,  O_EXCL,     O_NOCTTY,  O_TRUNC,   O_APPEND, O_NONBLOCK, O_SYNC,      O_DSYNC,
      O_DIRECT, O_NOFOLLOW, O_NOATIME, O_CLOEXEC, O_PATH,   O_TMPFILE,  O_DIRECTORY, O_ASYNC,
  };
  for (int i = 0; i < 16; i++) {
    if ((flags & file_flags[i]) == file_flags[i]) {
      flags = flags & ~file_flags[i];
      if (!ret) {
        ret = g_strdup_printf("%s", get_open_flag_name(file_flags[i]));
      } else {
        ret = g_strdup_printf("%s|%s", ret, get_open_flag_name(file_flags[i]));
      }
    }
  }
  return ret;
}

const char *get_creation_mode(int64_t flags, int64_t mode) {
  char *ret = NULL;
  if ((flags & O_CREAT) == O_CREAT || (flags & O_TMPFILE) == O_TMPFILE) {
    ret = g_strdup_printf("%#3lo", (uint64_t)mode);
  }
  return ret;
}