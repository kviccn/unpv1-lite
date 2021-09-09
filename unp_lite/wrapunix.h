#ifndef __UNP_LITE_WRAPUNIX_H_
#define __UNP_LITE_WRAPUNIX_H_

#include <stddef.h>

void Write(int fd, void *buf, size_t nbytes);
void Close(int fd);

#endif
