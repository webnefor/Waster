

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "config.h"
#include <pthread.h>
#include <string.h>
#include <netinet/in.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>
#include <stdarg.h>
#include <fcntl.h>

#define THREAD_COUNT(a, b) (a-b)


typedef struct {
    int host[255];
    int ports[255];
    int count;
} info_of_the_host;

__attribute__((unused)) extern int kernelThread(intervalRange * options);
