//
// Created by oleksandra on 17/11/24.
//

#include "connection.h"
#include "server.h"

static void recv_error(int cnt_fd) {
    char *msg1 = "error occurred while receiving data from socket ";
    char *msg2 = mx_strjoin(msg1, mx_itoa(cnt_fd));
    char *msg = mx_strjoin(msg2, "\n");
    logger_warn(msg);
    free(msg2);
    free(msg);
}

static void disconnected(int cnt_fd) {
    char *msg1 = "connection on the socket ";
    char *msg2 = mx_strjoin(msg1, mx_itoa(cnt_fd));
    char *msg = mx_strjoin(msg2, " disconnected\n");
    logger_info(msg);
    free(msg2);
    free(msg);
}

void *mx_handle_connection(void *socket_ptr) {
    int cnt_socket = *(int *)socket_ptr;
    free(socket_ptr);

    char buffer[1024];
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(cnt_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';

            char *msg1 = "received data from connection on the socket ";
            char *msg2 = mx_strjoin(msg1, mx_itoa(cnt_socket));
            char *msg = mx_strjoin(msg2, "\n");
            logger_debug(msg);
            free(msg2);
            free(msg);

            char *response = mx_handle_request(buffer);

            // send response back to the client

        } else if (bytes_received == 0) {
            disconnected(cnt_socket);
            break;
        } else {
            recv_error(cnt_socket);
            // call a function that forms json response whit "internal server error" status
            // now in development
        }
    }

    close(cnt_socket);
    return NULL;
}
