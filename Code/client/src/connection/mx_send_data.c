//
// Created by oleksandra on 17/11/24.
//

#include "connection.h"
#include "logger.h"
#include "libmx.h"
#include "utils.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <time.h>

#define TIMEOUT_SECONDS 5
#define BUFFER_SIZE 1024

static int get_amount(const char *data) {
    int data_len = mx_strlen(data);
    return (data_len + BUFFER_SIZE - 2) / (BUFFER_SIZE - 1);
}


static int send_with_timeout(int fd, const char *buffer, int buffer_size) {
    struct timespec start, current;
    clock_gettime(CLOCK_MONOTONIC, &start);

    int total_sent = 0;
    while (total_sent < buffer_size) {
        int sent = send(fd, buffer + total_sent, buffer_size - total_sent, 0);
        if (sent < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                clock_gettime(CLOCK_MONOTONIC, &current);
                double elapsed = (current.tv_sec - start.tv_sec) + (current.tv_nsec - start.tv_nsec) / 1e9;
                if (elapsed > TIMEOUT_SECONDS) {
                    char *msg = mx_sprintf("send_with_timeout: Timeout occurred while sending to socket %d\n", fd);
                    logger_error(msg);
                    free(msg);
                    return -1;
                }
                continue; // Socket temporarily unavailable, retry
            } else {
                char *msg = mx_sprintf("send_with_timeout: Error occurred sending data to socket %d\n", fd);
                logger_error(msg);
                free(msg);
                return -1;
            }
        }
        total_sent += sent;
    }
    return 0;
}

static int send_amount(int fd, int amount) {
    char *num_str = mx_itoa(amount);
    char buffer[BUFFER_SIZE];
    mx_memset(buffer, '\0', mx_strlen(buffer));
    mx_strncpy(buffer, num_str, mx_strlen(num_str));
    free(num_str);
    return send_with_timeout(fd, buffer, BUFFER_SIZE);

//    old way
//    if (send(fd, buffer, 1024, 0) < 0) {
//        char *msg = mx_sprintf("mx_send_data: Error occurred sending data to the socket %d\n", fd);
//        logger_error(msg);
//        free(msg);
//        return -1;
//    }
//    return 0;
}

static int send_content( int fd, int amount, char *data) {
    for (int i = 0; i < amount; ++i) {
        int len = (strlen(data) > (BUFFER_SIZE - 1)) ? (BUFFER_SIZE - 1) : mx_strlen(data);
        char buffer[BUFFER_SIZE];
        mx_memset(buffer, '\0', BUFFER_SIZE);

        mx_strncpy(buffer, data, len);
        data += len;

        if (send_with_timeout(fd, buffer, BUFFER_SIZE) < 0) {
            char *msg = mx_sprintf("send_content: Error occurred sending data chunk to socket %d\n", fd);
            logger_error(msg);
            free(msg);
            return -1;
        }
    }
    return 0;
}

int mx_send_data(char *data) {
    if (!data) {
        char *msg = mx_sprintf("mx_send_data: No data to send to the socket %d\n", fd);
        logger_error(msg);
        free(msg);
        return -1;  // no data to send
    }
    int amount = get_amount(data);
    if (send_amount(fd, amount) < 0) {
        char *msg = mx_sprintf("mx_send_data: Error occurred sending data to the socket %d\n", fd);
        logger_error(msg);
        free(msg);
        return -1;
    }
    if (send_content(fd, amount, data) < 0) {
        char *msg = mx_sprintf("mx_send_data: Error occurred sending data to the socket %d\n", fd);
        logger_error(msg);
        free(msg);
        return -1;
    }
    return 0;
}
