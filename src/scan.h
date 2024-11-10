

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <netinet/in.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>
#include <stdarg.h>
#include <fcntl.h>

#include "config.h"


typedef struct {

    char host[0xFFFF];
    int ports[0xFF];
    int count;

} info_of_the_host;

static uint32_t x = 0, totalIterations = 1;

static uintmax_t one = 0;
static uintmax_t two = 0;
static uintmax_t three = 0;
static uintmax_t four = 0;


__attribute__((unused)) extern int kernelThread(intervalRange * options);

int get_host_data(int sockfd, struct sockaddr_in * server_addr, char *);
