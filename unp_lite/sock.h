#ifndef __UNP_LITE_SOCK_H_
#define __UNP_LITE_SOCK_H_

#include <arpa/inet.h>

char *sock_ntop(const struct sockaddr *sa, socklen_t salen);
char *Sock_ntop(const struct sockaddr *sa, socklen_t salen);

char *sock_ntop_host(const struct sockaddr *sa, socklen_t salen);
char *Sock_ntop_host(const struct sockaddr *sa, socklen_t salen);

int sock_bind_wild(int sockfd, int family);
int Sock_bind_wild(int sockfd, int family);

int sock_cmp_addr(const struct sockaddr *sa1, const struct sockaddr *sa2, socklen_t salen);
int sock_cmp_port(const struct sockaddr *sa1, const struct sockaddr *sa2, socklen_t salen);

int sock_get_port(const struct sockaddr *sa, socklen_t salen);

void sock_set_port(struct sockaddr *sa, socklen_t salen, int port);
void sock_set_addr(struct sockaddr *sa, socklen_t salen, const void *addr);
void sock_set_wild(struct sockaddr *sa, socklen_t salen);

#endif
