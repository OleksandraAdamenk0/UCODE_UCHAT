//
// Created by oleksandra on 17/11/24.
//

#include "connection.h"
#include "libmx.h"
#include "utils.h"

#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

static int receive_amount(int fd) {
    char buffer[BUFFER_SIZE];
    mx_memset(buffer, '\0', sizeof(buffer));
    int bytes_received = recv(fd, buffer, sizeof(buffer), 0);
    if (bytes_received == 0) return -1;
    else if (bytes_received < 0) return -2;
    if (!mx_is_numeric(buffer)) return -3;

    int amount = mx_atoi(buffer);
    if (amount <= 0) return -3;

    return amount;
}

static int receive_content(int fd, int amount, char **result) {
    *result = NULL;

    for (int i = 0; i < amount; ++i) {
        char buffer[BUFFER_SIZE + 1] = {0};
        mx_memset(buffer, '\0', BUFFER_SIZE);

        int bytes_received = recv(fd, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received == 0) return -1;
        else if (bytes_received < 0) return -2;

        char *temp = mx_strjoin(*result, buffer);
        if (*result) free(*result);
        *result = temp;
    }
    return 0;
}

int mx_receive_data(int fd, char **data) {
    int amount = receive_amount(fd);
    if (amount < 0) return amount;

    int status = receive_content(fd, amount, data);
    if (status < 0) return status;

    return 0;
}
