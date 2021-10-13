#ifndef __UNP_LITE_WRAPSOCK_H_
#define __UNP_LITE_WRAPSOCK_H_

#include <arpa/inet.h>

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
int Socket(int family, int type, int protocol);

void Bind(int fd, const struct sockaddr *sa, socklen_t salen);
void Listen(int fd, int backlog);

const char *Inet_ntop(int family, const void *addrptr, char *strptr, size_t len);
void Inet_pton(int family, const char *strptr, void *addrptr);

#endif
