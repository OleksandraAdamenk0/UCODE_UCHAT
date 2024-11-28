//
// Created by oleksandra on 24/11/24.
//

#include "connection.h"
#include "libmx.h"
#define BUFFER_SIZE 1024

static int receive_amount(int fd) {
    char buffer[1024];
    mx_memset(buffer, '\0', sizeof(buffer));

    int bytes_received = recv(fd, buffer, sizeof(buffer), 0);

    // printf("amount of data chunks: %s\n", buffer);

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
        // printf("Received chunk %d/%d: '%s'\n", i + 1, amount, buffer);
        if (bytes_received == 0) return -1;
        else if (bytes_received < 0) return -2;

        char *temp = mx_strjoin(*result, buffer);
        free(*result);
        *result = temp;

        // printf("Received chunk %d/%d: %s\n", i + 1, amount, buffer);
    }

    return 0;
}

int mx_receive_data(int fd, char **data) {
    int amount = receive_amount(fd);
    if (amount < 0) return amount;
    // printf("amount of data chunks in main: %d\n", amount);

    int status = receive_content(fd, amount, data);
    if (status < 0) return status;

    // printf("All data received: %s\n", *data);
    return 0;
}