//
// created by herman on 22/11/24.
//

#include "connection.h"
#include "logger.h"
#include "libmx.h"
#include "utils.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <errno.h>

#define BUFFER_SIZE 1024
#define TIMEOUT_SECONDS 5

static int wait_for_data(int fd) {
    fd_set read_fds;
    struct timeval timeout;

    FD_ZERO(&read_fds);
    FD_SET(fd, &read_fds);

    timeout.tv_sec = TIMEOUT_SECONDS;
    timeout.tv_usec = 0;

    char *msg = mx_sprintf("Waiting for data on socket %d...", fd);
    logger_debug(msg);
    free(msg);
    int result = select(fd + 1, &read_fds, NULL, NULL, &timeout);
    if (result == -1) {
        msg = mx_sprintf("Select error while waiting for data on socket %d", fd);
        logger_error(msg);
        free(msg);
        return -1;
    } else if (result == 0) {
        msg = mx_sprintf("Timeout waiting for data on socket %d", fd);
        logger_error(msg);
        free(msg);
        return -1;
    }

    msg = mx_sprintf("Data is ready to read on socket %d", fd);
    logger_debug(msg);
    free(msg);
    return 0;
}

static int receive_amount(int fd) {
    char buffer[BUFFER_SIZE];
    mx_memset(buffer, '\0', BUFFER_SIZE);

    logger_debug("Attempting to receive the amount of chunks...");
    if (wait_for_data(fd) < 0) {
        char *msg = mx_sprintf("Timeout or error while waiting for the amount on socket %d", fd);
        logger_error(msg);
        free(msg);
        return -1;
    }
    int bytes_received = recv(fd, buffer, BUFFER_SIZE, 0);

    if (bytes_received == 0) {
        char *msg = mx_sprintf("Connection closed by peer while receiving the amount on socket %d", fd);
        logger_error(msg);
        free(msg);
        return -1;
    } else if (bytes_received < 0) {
        char *msg = mx_sprintf("Error receiving the amount on socket %d", fd);
        logger_error(msg);
        free(msg);
        return -2;
    }

    if (!mx_is_numeric(buffer)) {
        char *msg = mx_sprintf("\"Received non-numeric data for the amount: %s", buffer);
        logger_error(msg);
        free(msg);
        return -3;
    }

    int amount = mx_atoi(buffer);
    if (amount <= 0) {
        char *msg = mx_sprintf("\"Invalid amount received: %d", amount);
        logger_error(msg);
        logger_debug(buffer);
        free(msg);
        return -3;
    }

    char *msg = mx_sprintf("\"Amount received: %d", amount);
    logger_error(msg);
    free(msg);
    return amount;
}

static int receive_content(int fd, int amount, char **result) {
    *result = NULL;

    for (int i = 0; i < amount; ++i) {
        char buffer[BUFFER_SIZE + 1] = {0};
        mx_memset(buffer, '\0', BUFFER_SIZE);

        if (wait_for_data(fd) < 0) {
            char *msg = mx_sprintf("Timeout or error while waiting for chunk %d/%d on socket %d", i + 1, amount, fd);
            logger_error(msg);
            return -1;
        }

        int bytes_received = recv(fd, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received == 0) return -1;
        else if (bytes_received < 0) return -2;

        char *temp = mx_strjoin(*result, buffer);
        free(*result);
        *result = temp;
    }

    logger_info("All chunks successfully received");
    return 0;
}

int mx_receive_data(char **data) {
    int amount = receive_amount(fd);
    if (amount < 0) {
        logger_error("Error receiving data");
        return amount;
    }

    int status = receive_content(fd, amount, data);
    if (status < 0) return status;
    logger_info("Data received");
    logger_debug(*data);
    return 0;
}
