#include "unp_lite.h"

void Write(int fd, void *buf, size_t nbytes) {
  if (write(fd, buf, nbytes) != nbytes) {
    err_sys("write error");
  }
}

void Close(int fd) {
  if (close(fd) == -1) {
    err_sys("close error");
  }
}
