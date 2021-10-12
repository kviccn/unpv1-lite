#ifndef __UNP_LITE_READWRITE_H_
#define __UNP_LITE_READWRITE_H_

#include <unistd.h>

ssize_t readn(int fd, void *ptr, size_t nbytes);
ssize_t Readn(int fd, void *ptr, size_t nbytes);

ssize_t writen(int fd, const void *ptr, size_t nbytes);
void Writen(int fd, const void *ptr, size_t nbytes);

ssize_t readline(int fd, void *vptr, size_t maxlen);
ssize_t readlinebuf(void **vptrptr);
ssize_t Readline(int fd, void *ptr, size_t maxlen);

#endif
