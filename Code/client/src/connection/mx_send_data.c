//
// Created by oleksandra on 17/11/24.
//


#include "client.h"
#include "connection.h"
#define BUFFER_SIZE 1024

static void null_data(int cnt_socket) {
    char *msg1 = "error occurred trying to send data to the socket ";
    char *msg2 = mx_strjoin(msg1, mx_itoa(cnt_socket));
    char *msg = mx_strjoin(msg2, ": data is NULL\n");
    logger_debug(msg);
    free(msg2);
    free(msg);
}

static void close_connection(int cnt_socket) {
    char *msg1 = "connection ";
    char *msg2 = mx_strjoin(msg1, mx_itoa(cnt_socket));
    char *msg = mx_strjoin(msg2, " closed during data send\n");
    logger_debug(msg);
    free(msg2);
    free(msg);
}

static void error_sending(int cnt_socket) {
    char *msg1 = "error sending data to the socket ";
    char *msg2 = mx_strjoin(msg1, mx_itoa(cnt_socket));
    char *msg = mx_strjoin(msg2, "\n");
    logger_debug(msg);
    free(msg2);
    free(msg);
}

static int get_amount(const char *data) {
    int data_len = mx_strlen(data);
    return (data_len + BUFFER_SIZE - 2) / (BUFFER_SIZE - 1);
}

static int send_amount(int fd, int amount) {
    char *num_str = mx_itoa(amount);
    char buffer[1024];
    mx_memset(buffer, '\0', mx_strlen(buffer));
    mx_strncpy(buffer, num_str, mx_strlen(num_str));
    if (send(fd, buffer, 1024, 0) < 0) {
        error_sending(fd);
        return -1;
    }
    return 0;
}

static int send_content( int fd, int amount, char *data) {
    for (int i = 0; i < amount; ++i) {
        int len = (strlen(data) > (BUFFER_SIZE - 1)) ? (BUFFER_SIZE - 1) : mx_strlen(data);
        char buffer[BUFFER_SIZE];
        mx_memset(buffer, '\0', BUFFER_SIZE);

        mx_strncpy(buffer, data, len);
        data += len;

        if (send(fd, buffer, 1024, 0) < 0)
            return -1;
    }
    return 0;
}

int mx_send_data(char *data) {
    if (!data) {
        null_data(fd);
        return -1;  // no data to send
    }
    int amount = get_amount(data);
    if (send_amount(fd, amount) < 0) {
        error_sending(fd);
        return -1;
    }
    if (send_content(fd, amount, data) < 0) {
        error_sending(fd);
        return -1;
    }
    return 0;
}
