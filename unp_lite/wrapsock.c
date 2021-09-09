#include "unp_lite.h"

int Socket(int family, int type, int protocol) {
  int sockfd;
  if ((sockfd = socket(family, type, protocol)) < 0) {
    err_sys("socket error");
  }
  return sockfd;
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen) {
  if (bind(fd, sa, salen) < 0) {
    err_sys("connect error");
  }
}

void Listen(int fd, int backlog) {
  char *listenq;
  if ((listenq = getenv("LISTENQ")) != NULL) {
    backlog = atoi(listenq);
  }

  if (listen(fd, backlog) < 0) {
    err_sys("listen error");
  }
}

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr) {
  int connfd;

again:
  if ((connfd = accept(fd, sa, salenptr)) < 0) {
#ifdef EPROTO
    if (errno == EPROTO || errno == ECONNABORTED) {
#else
    if (errno == ECONNABORTED) {
#endif
      goto again;
    } else {
      err_sys("accept error");
    }
  }
  return connfd;
}
