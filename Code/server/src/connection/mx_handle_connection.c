//
// Created by oleksandra on 17/11/24.
//

#include "connection.h"
#include "server.h"

static char *msg_with_fd(char *msg, int fd) {
    char *msg1 = "Socket: ";
    char *msg2 = mx_itoa(fd);
    char *msg3 = mx_strjoin(msg1, msg2);
    char *msg4 = mx_strjoin(msg3, ". Msg: ");
    char *msg5 = mx_strjoin(msg4, msg);
    free(msg2);
    free(msg3);
    free(msg4);
    if (msg5[mx_strlen(msg5) - 1] != '\n') {
        char *msg6 = mx_strjoin(msg5, "\n");
        free(msg5);
        return msg6;
    }
    return msg5;
}

static void handle_recv_error(int status, int fd) {
    if (status == -1) {
        char *msg = msg_with_fd("Client disconnected\n", fd);
        logger_info(msg);
        free(msg);
    } else if (status == -2) {
        char *msg = msg_with_fd("Error receiving data\n", fd);
        logger_error(msg);
        free(msg);
    } else if (status == -3){
        char *msg = msg_with_fd("Wrong data size format\n", fd);
        logger_error(msg);
        free(msg);
    } else {
        char *msg = msg_with_fd("Unknown error\n", fd);
        logger_error(msg);
        free(msg);
    }
}

static void handle_send_error(int status, int fd) {
    if (status == -1) {
        char *msg = msg_with_fd("Trying to send NULL data\n", fd);
        logger_debug(msg);
        free(msg);
    } else if (status == -2) {
        char *msg = msg_with_fd("Error sending chunk amount\n", fd);
        logger_debug(msg);
        free(msg);
    } else if (status == -3) {
        char *msg = msg_with_fd("Error sending data content\n", fd);
        logger_debug(msg);
        free(msg);
    } else {
        char *msg = msg_with_fd("Unknown error\n", fd);
        logger_debug(msg);
        free(msg);
    }
}

static void handle_request(char *request, int fd) {
    char *msg = msg_with_fd("Received data from connection\n", fd);
    logger_error(msg);
    free(msg);

    char *response = mx_handle_request(request);
    if (!response) {
        msg = msg_with_fd("Can not send the response because of the"
                                " request handling error\n", fd);
        logger_debug(msg);
        free(msg);
        return;
    }
    int status = mx_send_data(fd, response);

    free(response);
    if (status < 0) {
        msg = msg_with_fd("Error sending data\n", fd);
        logger_error(msg);
        free(msg);
        handle_send_error(status, fd);
    }
}

void *mx_handle_connection(void *data) {
    t_client_info *info = (t_client_info *)data;

    while (1) {
        char *request = NULL;
        int status = mx_receive_data(*(info->fd), &request);
        if (status < 0) {
            handle_recv_error(status, *(info->fd));
            if (request) {
                free(request);
                request = NULL;
            }
            if (status == -1) break;
            continue;
        }
        handle_request(request, *(info->fd));
        free(request);
    }
    mx_finalize_client(info);
    pthread_exit(NULL);
}
