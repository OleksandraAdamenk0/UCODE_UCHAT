//
// Created by oleksandra on 17/11/24.
//

#include "client.h"
#include "connection.h"

int fd;

static int create_socket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) return -1;
    return sockfd;
}

static struct sockaddr_in create_address() {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    return addr;
}

static int setup_non_blocking_mode(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) return -1;
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) return -1;
    return 0;
}

static int setup_blocking_mode(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) return -1;
    if (fcntl(sockfd, F_SETFL, flags) == -1) return -1;
    return 0;
}

static int check_time_out(int sockfd) {
    fd_set writefds;
    struct timeval tv;
    FD_ZERO(&writefds);
    FD_SET(sockfd, &writefds);
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    return select(sockfd + 1, NULL, &writefds, NULL, &tv);
}

static int connection(int sockfd) {
    struct sockaddr_in server_addr = create_address();
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0)
        return -1;

    // set up non-blocking mode to get control back to the program
    // without waiting for connect to be executed
    if (setup_non_blocking_mode(sockfd) < 0) {
        logger_warn("an attempt to set up a non-blocking mode "
                    "for the connection to the server failed\n");

        if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            logger_fatal("an internal client error occurred "
                         "while trying to connect to the server\n");
            return -1;
        }
        return 0;
    }

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        // if errno == EINPROGRESS then there is no error occurred
        // but client is still trying to connect to the server
        if (errno != EINPROGRESS) {
            logger_fatal("an internal client error occurred "
                         "while trying to connect to the server\n");
            return -1;
        }
    }

    int result = check_time_out(sockfd);

    if (result == 0) logger_fatal("connection attempt to server timed out\n");
    else if (result < 0) logger_fatal("an internal client error occurred "
                                      "while trying to connect to the server\n");

    // set up socket back to blocking mode
    if (setup_blocking_mode(sockfd) < 0) {
        logger_warn("an attempt to set up a blocking mode "
                    "for the connection to the server failed\n");
    }

    if (result > 0) return 0;
    if (result < 0) return -1;
    return -2; // to know that the app is in offline mode
}

int mx_open_connection() {
    fd = create_socket();
    if (fd < 0) {
        logger_error("error occurred while creating socket\n");
        return -1;
    }
    else logger_info("socket was created successfully\n");

    int status = connection(fd);
    if (status < 0){
        mx_close_connection(fd);
        return status;
    }
    return fd;
}
