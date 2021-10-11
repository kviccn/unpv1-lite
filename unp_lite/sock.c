#include "unp_lite.h"

char *sock_ntop(const struct sockaddr *sa, socklen_t salen) {
  char portstr[8];
  static char str[128];

  switch (sa->sa_family) {
    case AF_INET: {
      struct sockaddr_in *sin = (struct sockaddr_in *)sa;

      if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL) {
        return NULL;
      }

      if (ntohs(sin->sin_port) != 0) {
        snprintf(portstr, sizeof(portstr), ":%d", ntohs(sin->sin_port));
        strcat(str, portstr);
      }
      return str;
    }
    case AF_INET6: {
      struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;

      str[0] = '[';
      if (inet_ntop(AF_INET6, &sin6->sin6_addr, str + 1, sizeof(str) - 1) == NULL) {
        return NULL;
      }

      if (ntohs(sin6->sin6_port) != 0) {
        snprintf(portstr, sizeof(portstr), "]:%d", ntohs(sin6->sin6_port));
        strcat(str, portstr);
        return str;
      }
      return str + 1;
    }
    case AF_UNIX: {
      struct sockaddr_un *un = (struct sockaddr_un *)sa;

      if (un->sun_path[0] == 0) {
        strcpy(str, "(no pathname bound)");
      } else {
        snprintf(str, sizeof(str), "%s", un->sun_path);
      }
      return str;
    }
    default: {
      snprintf(str, sizeof(str), "sock_ntop: unknown AF_xxx: %d, len %d", sa->sa_family, salen);
      return str;
    }
  }
  return NULL;
}

char *Sock_ntop(const struct sockaddr *sa, socklen_t salen) {
  char *ptr;
  if ((ptr = sock_ntop(sa, salen)) == NULL) {
    err_sys("sock_ntop error");
  }
  return ptr;
}

char *sock_ntop_host(const struct sockaddr *sa, socklen_t salen) {
  static char str[128];

  switch (sa->sa_family) {
    case AF_INET: {
      struct sockaddr_in *sin = (struct sockaddr_in *)sa;

      if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL) {
        return NULL;
      }
      return str;
    }
    case AF_INET6: {
      struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;

      if (inet_ntop(AF_INET6, &sin6->sin6_addr, str, sizeof(str)) == NULL) {
        return NULL;
      }
      return str;
    }
    case AF_UNIX: {
      struct sockaddr_un *un = (struct sockaddr_un *)sa;

      if (un->sun_path[0] == 0) {
        strcpy(str, "(no pathname bound)");
      } else {
        snprintf(str, sizeof(str), "%s", un->sun_path);
      }
      return str;
    }
    default: {
      snprintf(str, sizeof(str), "sock_ntop_host: unknown AF_xxx %d, len %d", sa->sa_family, salen);
      return str;
    }
  }
  return NULL;
}

char *Sock_ntop_host(const struct sockaddr *sa, socklen_t salen) {
  char *ptr;
  if ((ptr = sock_ntop_host(sa, salen)) == NULL) {
    err_sys("sock_ntop_host error");
  }
  return ptr;
}

int sock_bind_wild(int sockfd, int family) {
  socklen_t len;

  switch (family) {
    case AF_INET: {
      struct sockaddr_in sin;

      bzero(&sin, sizeof(sin));
      sin.sin_family = AF_INET;
      sin.sin_addr.s_addr = htonl(INADDR_ANY);
      sin.sin_port = htons(0);  // 由系统确定端口

      if (bind(sockfd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        return -1;
      }

      len = sizeof(sin);
      if (getsockname(sockfd, (struct sockaddr *)&sin, &len) < 0) {
        return -1;
      }
      return sin.sin_port;
    }
    case AF_INET6: {
      struct sockaddr_in6 sin6;

      bzero(&sin6, sizeof(sin6));
      sin6.sin6_family = AF_INET6;
      sin6.sin6_addr = in6addr_any;
      sin6.sin6_port = htons(0);

      if (bind(sockfd, (struct sockaddr *)&sin6, sizeof(sin6)) < 0) {
        return -1;
      }

      len = sizeof(sin6);
      if (getsockname(sockfd, (struct sockaddr *)&sin6, &len) < 0) {
        return -1;
      }
      return sin6.sin6_port;
    }
  }
  return -1;
}

int Sock_bind_wild(int sockfd, int family) {
  int port;
  if ((port = sock_bind_wild(sockfd, family)) < 0) {
    err_sys("sock_bind_wild error");
  }
  return port;
}

int sock_cmp_addr(const struct sockaddr *sa1, const struct sockaddr *sa2, socklen_t salen) {
  if (sa1->sa_family != sa2->sa_family) {
    return -1;
  }

  switch (sa1->sa_family) {
    case AF_INET: {
      return memcmp(&((struct sockaddr_in *)sa1)->sin_addr, &((struct sockaddr_in *)sa2)->sin_addr,
                    sizeof(struct in_addr));
    }
    case AF_INET6: {
      return memcmp(&((struct sockaddr_in6 *)sa1)->sin6_addr,
                    &((struct sockaddr_in6 *)sa2)->sin6_addr, sizeof(struct in6_addr));
    }
    case AF_UNIX: {
      return strcmp(((struct sockaddr_un *)sa1)->sun_path, ((struct sockaddr_un *)sa2)->sun_path);
    }
  }
  return -1;
}

int sock_cmp_port(const struct sockaddr *sa1, const struct sockaddr *sa2, socklen_t salen) {
  if (sa1->sa_family != sa2->sa_family) {
    return -1;
  }

  switch (sa1->sa_family) {
    case AF_INET: {
      return ((struct sockaddr_in *)sa1)->sin_port == ((struct sockaddr_in *)sa2)->sin_port;
    }
    case AF_INET6: {
      return ((struct sockaddr_in6 *)sa1)->sin6_port == ((struct sockaddr_in6 *)sa2)->sin6_port;
    }
  }
  return -1;
}

int sock_get_port(const struct sockaddr *sa, socklen_t salen) {
  switch (sa->sa_family) {
    case AF_INET: {
      struct sockaddr_in *sin = (struct sockaddr_in *)sa;
      return sin->sin_port;
    }
    case AF_INET6: {
      struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;
      return sin6->sin6_port;
    }
  }
  return -1;
}

void sock_set_port(struct sockaddr *sa, socklen_t salen, int port) {
  switch (sa->sa_family) {
    case AF_INET: {
      struct sockaddr_in *sin = (struct sockaddr_in *)sa;
      sin->sin_port = port;
      return;
    }
    case AF_INET6: {
      struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;
      sin6->sin6_port = port;
      return;
    }
  }
  return;
}

void sock_set_addr(struct sockaddr *sa, socklen_t salen, const void *addr) {
  switch (sa->sa_family) {
    case AF_INET: {
      struct sockaddr_in *sin = (struct sockaddr_in *)sa;
      memcpy(&sin->sin_addr, addr, sizeof(struct in_addr));
      return;
    }
    case AF_INET6: {
      struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;
      memcpy(&sin6->sin6_addr, addr, sizeof(struct in6_addr));
      return;
    }
  }
  return;
}

void sock_set_wild(struct sockaddr *sa, socklen_t salen) {
  const void *wildptr;

  switch (sa->sa_family) {
    case AF_INET: {
      static struct in_addr in4addr_any;

      in4addr_any.s_addr = htonl(INADDR_ANY);
      wildptr = &in4addr_any;
      break;
    }
    case AF_INET6: {
      wildptr = &in6addr_any;
      break;
    }
    default:
      return;
  }
  sock_set_addr(sa, salen, wildptr);
  return;
}
