//
// Created by oleksandra on 17/11/24.
//

#include "connection.h"
#include "server.h"

static void send_error(int cnt_fd) {
    char *msg1 = "error occurred while sending data to the socket ";
    char *msg2 = mx_strjoin(msg1, mx_itoa(cnt_fd));
    char *msg = mx_strjoin(msg2, "\n");
    logger_warn(msg);
    free(msg2);
    free(msg);
}


static void recv_error(int cnt_fd) {
    char *msg1 = "error occurred while receiving data from socket ";
    char *msg2 = mx_strjoin(msg1, mx_itoa(cnt_fd));
    char *msg = mx_strjoin(msg2, "\n");
    logger_warn(msg);
    free(msg2);
    free(msg);
}

static void disconnected(int fd) {
    char *msg1 = "connection on the socket ";
    char *msg2 = mx_strjoin(msg1, mx_itoa(fd));
    char *msg = mx_strjoin(msg2, " disconnected\n");
    logger_info(msg);
    free(msg2);
    free(msg);
}

static void recv_data(int fd) {
    char *msg1 = "received data from connection on the socket ";
    char *msg2 = mx_strjoin(msg1, mx_itoa(fd));
    char *msg = mx_strjoin(msg2, "\n");
    logger_debug(msg);
    free(msg2);
    free(msg);
}

static void size_format_error(int fd) {
    char *msg1 = "wrong data size format received from connection on the socket ";
    char *msg2 = mx_strjoin(msg1, mx_itoa(fd));
    char *msg = mx_strjoin(msg2, "\n");
    logger_error(msg);
    free(msg2);
    free(msg);
}

void *mx_handle_connection(void *data) {
    t_client_info *info = (t_client_info *)data;

    while (1) {
        char *request;
        int status = mx_receive_data(*(info->fd), &request);
        if (status == -1) {
            disconnected(*(info->fd));
            break;
        } else if (status == -2) {
            recv_error(*(info->fd));
            continue;
        } else if (status == -3){
            size_format_error(*(info->fd));
            continue;
        } else {
            // got request from client
            char *response = mx_handle_request(request);
            if (!response) {
                logger_error("can not send the response "
                             "because of the error during request handling\n");
                continue;
            }
            if (mx_send_data(*(info->fd), response) < 0)
                send_error(*(info->fd));
        }
    }
    mx_finalize_client(info);
    pthread_exit(NULL);
}
