#ifndef __UNP_LITE_H_
#define __UNP_LITE_H_

#include <arpa/inet.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#define MAXLINE 4096

// error
void err_quit(const char *fmt, ...);
void err_sys(const char *fmt, ...);

#endif
