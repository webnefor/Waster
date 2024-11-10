
#include "scan.h"


void parse_server_info(const char *response) {

    const char *server_header = "Server: ";
    const char *version_header = "Version: ";

    char server_info[1024];
    char server_version[1024];

    char *server_start = strstr(response, server_header);
    if (server_start) {
        server_start += strlen(server_header);
        char *server_end = strstr(server_start, "\r\n");
        if (server_end) {
            *server_end = '\0';
            strcpy(server_info, server_start);
        }
    }

    char *version_start = strstr(response, version_header);
    if (version_start) {
        version_start += strlen(version_header);
        char *version_end = strstr(version_start, "\r\n");
        if (version_end) {
            *version_end = '\0';
            strcpy(server_version, version_start);
        }
    }

    strcpy(response, server_info);
    sprintf(response + (strlen(server_info)), server_version);
}
//


int get_host_data(int port, struct sockaddr_in *server_addr, char *response) {

    char request[4096];
    char buffer[1222];
    int sock;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        pthread_exit(NULL);

    snprintf(

            request,
            sizeof(request),
            "GET / HTTP/1.1\r\n"
            "Connection: close\r\n\r\n",
            inet_ntoa(server_addr->sin_addr)

            );

    server_addr->sin_port = htons(port);

    if (connect(sock, (struct sockaddr *)server_addr, sizeof(*server_addr)) < 0) {
//        perror("Connect failed");
        close(sock);
        return 1;
    }

    if (send(sock, request, strlen(request), 0) < 0) {
//        perror("Send failed");
        close(sock);
        return 1;
    }

    ssize_t bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);

    if (bytes_received < 0) {
//        perror("Receive failed");
        close(sock);
        return 1;
    }

    buffer[bytes_received] = '\0';

    parse_server_info(buffer);

    strncpy(response, buffer, bytes_received + 1); // +1 to include null terminator

    close(sock);

    return 0;
}

__attribute__ ((unused)) int hostScan(info_of_the_host * addr) {

    int count = 0;  int activePorts[addr->count];
    int sock;       int status;
    int result;     int flags;

    int p_port;

    off_t offset;
    socklen_t len;
    fd_set write_fds;

    char response[1024];

    struct sockaddr_in server_addr;
    struct timeval timeout;

    memset(&server_addr, 0, sizeof(server_addr));

    for (int i = 0; i < addr->count; i++)
    {
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            free(addr);
            pthread_exit(NULL);
        }

        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(addr->host);

        flags = fcntl(sock, F_GETFL, 0);
        fcntl(sock, F_SETFL, flags | O_NONBLOCK);

        server_addr.sin_port = htons(addr->ports[i]);

        status = connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr));

        if (status == -1 && errno != EINPROGRESS && errno != EWOULDBLOCK)
        {
            close(sock);
            continue;
        }

        FD_ZERO(&write_fds);
        FD_SET(sock, &write_fds);

        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        result = select(sock + 1, NULL, &write_fds, NULL, &timeout);

        if (result <= 0)
        {
            if (result == 0)
                continue;
            else
                continue;
        }

        len = sizeof(int);

        if (getsockopt(sock, SOL_SOCKET, SO_ERROR, &result, &len) < 0)
        {
            close(sock);
            continue;
        }

        if (result != 0)
        {
            errno = result;
            close(sock);
            continue;
        }

        if (((p_port = addr->ports[i]) == 80) || ((p_port = addr->ports[i]) == 443))
            get_host_data(p_port, &server_addr, response);

        activePorts[count] = addr->ports[i];

        count += 1;

        fcntl(sock, F_SETFL, flags);
    }

    char buffer[count];

    if (count > 0) {

        offset = 0;

        for (int i = 0; i < count; i++)
            offset += sprintf(buffer + offset, "[%d]", activePorts[i]);

        printf(
                "\033[035m[%s]" "\033[031m" " (%s) " DEFAULT "\n\t" "\033[032m" "└───" "%s " "\n",
                addr->host,
                response,
                buffer
        );
    }

    free(addr);

    pthread_exit(NULL);

}

uint32_t Loop(intervalRange *args) {

    uint32_t range = 0;
    pthread_t threads[1024];

    static int i = 0;

    for (;; i++) {
        int temp = i;

        if (range >= 50 || range >= x) {
            break;
        }

        uintmax_t four = 0, three = 0, two = 0, one = 0;
        uintmax_t *pInt[] = {&four, &three, &two, &one};

        for (int j = 4; j > 0; j--) {
            size_t index = temp % (args->end[j - 1] - args->begin[j - 1] + 1);
            *pInt[j - 1] = (uintmax_t)(args->begin[j - 1] + index);
            temp /= (args->end[j - 1] - args->begin[j - 1] + 1);
        }

        info_of_the_host *threadArgs = malloc(sizeof(info_of_the_host));

        if (!threadArgs) {
            perror("Failed to allocate memory for thread arguments");
            exit(EXIT_FAILURE);
        }

        snprintf(threadArgs->host, sizeof(threadArgs->host), "%ju.%ju.%ju.%ju", four, three, two, one);
        threadArgs->count = args->PortsCount;
        memcpy(threadArgs->ports, args->ports, sizeof(args->ports));

        if (pthread_create(&threads[range], NULL, hostScan, threadArgs) != 0) {
            perror("Error creating thread");
            free(threadArgs);
            continue;
        }

        range++;
    }

    for (uint32_t e = 0; e < range; e++) {
        pthread_join(threads[e], NULL);
    }

    return range;
}

_Noreturn int kernelThread(intervalRange * args)
{
    for (uintmax_t i = 0; i < 4; i++)
        totalIterations *= ((args->end[i] - args->begin[i]) + 1);

    x = totalIterations;

    one     = args->begin[0] ;
    two     = args->begin[1] ;
    three   = args->begin[2] ;
    four    = args->begin[3] ;

    int * status;

    while (x)
    {
        status = (int *) (Loop(args));

        x -= (uint32_t)status;
    }

}
