//

#include "scan.h"


char * intToStr(int number) {
    int i = 0;
    int isNegative = 0;
    char *str = malloc(255);

    if (number < 0) {
        isNegative = 1;
        number = -number;
    }

    do {
        str[i++] = (number % 10) + '0';
        number /= 10;
    } while (number != 0);

    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    for (int j = 0; j < i / 2; ++j) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }

    return str;
}

__attribute__((unused)) int hostScan(info_of_the_host *addr) {
    int sockfd;
    struct sockaddr_in server_addr;

    fd_set write_fds;
    struct timeval timeout;
    int result;
    socklen_t len;
    int count = 0;
    int activePorts[addr->count];

    memset(&server_addr, 0, sizeof(server_addr));

    for (int i = 0; i < addr->count; i++)
    {
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            free(addr);
            pthread_exit(NULL);
        }

        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htonl(
                (addr->host[0] << 24) | (addr->host[1] << 16) | (addr->host[2] << 8) | addr->host[3]);

        int flags = fcntl(sockfd, F_GETFL, 0);
        fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
        server_addr.sin_port = htons(addr->ports[i]);

        int status = connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr));

        if (status == -1 && errno != EINPROGRESS && errno != EWOULDBLOCK)
        {
            close(sockfd);
            continue;
        }

        FD_ZERO(&write_fds);
        FD_SET(sockfd, &write_fds);
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        result = select(sockfd + 1, NULL, &write_fds, NULL, &timeout);

        if (result <= 0)
        {
            if (result == 0)
                continue;
            else
                continue;
        }

        len = sizeof(int);

        if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &result, &len) < 0)
        {
            close(sockfd);
            continue;
        }

        if (result != 0)
        {
            errno = result;
            close(sockfd);
            continue;
        }

        activePorts[count] = addr->ports[i];

        count +=1;
        fcntl(sockfd, F_SETFL, flags);
        close(sockfd);

    }

    // \n
    // └─

    char buffer[count];

    if (count > 0)
    {
        int offset = 0;

        for (int i = 0; i < count; i++) {
            offset += sprintf(buffer + offset, "[%d] ", activePorts[i]);
        }

        printf("\033[035m(%i.%i.%i.%i) -> " "\033[032m" "%s\n",
               addr->host[0],
               addr->host[1],
               addr->host[2],
               addr->host[3],
               buffer
               );
    }

    free(addr);
    pthread_exit(NULL);
}


_Noreturn int kernelThread(intervalRange * args)
{

    pthread_t threads[255];
    int i = 0;
    int j = 0;
    for (int one = args->begin[0];one <= args->end[0] ; one++)
        for (int two = args->begin[1]; two <= args->end[1]; two++)
            for (int three = args->begin[2]; three <= args->end[2]; three++)
                for (int four = args->begin[3]; four <= args->end[3]; four++)
                {
                    info_of_the_host *threadArgs = (info_of_the_host *)malloc(sizeof(info_of_the_host));
                    threadArgs->count = args->PortsCount;
                    memcpy(threadArgs->ports, args->ports, sizeof(args->ports));

                    threadArgs->host[0] = one;
                    threadArgs->host[1] = two;
                    threadArgs->host[2] = three;
                    threadArgs->host[3] = four;

                    pthread_create(&threads[i], NULL, (void *(*)(void *)) hostScan, (void *)threadArgs);

                    i+=1;
                }

    for(int t = 0; t < i; t++)
        pthread_join(threads[t], NULL);

    pthread_exit(NULL);
}