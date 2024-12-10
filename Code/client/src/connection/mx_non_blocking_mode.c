//
// Created by oleksandra on 04/12/24.
//

#include "connection.h"
#include "logger.h"
#include "utils.h"

#include <sys/socket.h>
#include <sys/time.h>
#include <errno.h>
#include <unistd.h>

static int check_connection_timeout(struct timeval *start_time) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    long elapsed_time = (current_time.tv_sec - start_time->tv_sec) * 1000 +
                        (current_time.tv_usec - start_time->tv_usec) / 1000;

    if (elapsed_time >= 10000) return -1;
    return 0;
}

static int select_connection(int sockfd, struct sockaddr_in *svr_addr, struct timeval *tv) {
    fd_set writefds;
    FD_ZERO(&writefds);
    FD_SET(sockfd, &writefds);

    int result = select(sockfd + 1, NULL, &writefds, NULL, tv);

    if (result < 0) {
        char *msg = mx_sprintf("select() error: %s", strerror(errno));
        logger_error(msg);
        mx_strdel(&msg);
        return -1;
    }

    if (result == 0) {
        logger_warn("Connection attempt timed out after select timeout");
        return -2;
    }

    int error = 0;
    socklen_t len = sizeof(error);
    if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
        char *msg = mx_sprintf("getsockopt failed: %s", strerror(errno));
        logger_error(msg);
        mx_strdel(&msg);
        return -1;
    }

    if (error != 0) {
        char *msg = mx_sprintf("Connection failed with error: %s", strerror(error));
        logger_warn(msg);
        mx_strdel(&msg);
        return -1;
    }
    if (error == 0) logger_info("Connected successfully");
    return 0;
}

static int handle_errors(int sockfd, struct sockaddr_in *svr_addr) {
    if (errno == EINPROGRESS) {
        struct timeval tv = {0, 500000};
        int status = select_connection(sockfd, svr_addr, &tv);
        if (status == 0) return 0;
        if (status == -1) return -1;
    } else if (errno == ECONNREFUSED) {
        logger_warn("Connection refused, retrying...");
        return -2;
    } else {
        char *msg = mx_sprintf("mx_non_blocking_mode: Connection failed"
                               " during select with unexpected error %s",
                               strerror(errno));
        logger_fatal(msg);
        free(msg);
    }
    return -2;
}

int mx_non_blocking_mode(int sockfd, struct sockaddr_in svr_addr) {
    logger_info("mx_non_blocking_mode: Trying to connect");
    struct timeval start_time;
    gettimeofday(&start_time, NULL);
    int result;

    while (1) {
        if (connect(sockfd, (struct sockaddr *) &svr_addr,sizeof(svr_addr)) == 0) {
            logger_info("mx_non_blocking_mode: Connected successfully");
            result = 0;
            break;
        }
        // not connected yet
        result = handle_errors(sockfd, &svr_addr);
        if (result == 0) break;

        if (check_connection_timeout(&start_time) < 0) {
            logger_warn("mx_non_blocking_mode: Connection attempt timed out");
            result = -2;
            break;
        }
        logger_warn("mx_non_blocking_mode: Connection attempt failed, retrying...");
        usleep(500000);
    }
    return result;
}
