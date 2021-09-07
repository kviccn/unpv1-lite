#include "unp_lite.h"

static void err_doit(bool errnoflag, const char *fmt, va_list ap) {
  int errno_save;
  char buf[MAXLINE];

  errno_save = errno;
  vsprintf(buf, fmt, ap);
  if (errnoflag) {
    sprintf(buf + strlen(buf), ": %s", strerror(errno_save));
  }
  strcat(buf, "\n");
  fflush(stdout);
  fputs(buf, stderr);
  fflush(stderr);
  return;
}

void err_quit(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(false, fmt, ap);
  va_end(ap);
  exit(1);
}

void err_sys(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(true, fmt, ap);
  va_end(ap);
  exit(1);
}
