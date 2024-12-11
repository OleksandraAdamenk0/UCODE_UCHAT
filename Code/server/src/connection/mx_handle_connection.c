//
// Created by oleksandra on 17/11/24.
//

#include "connection.h"
#include "request_processing.h"
#include "logger.h"
#include "utils.h"

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static void finalize_client(t_client_info *info) {
    if (info) {
        if (info->fd) close(info->fd);
        free(info);
    }
}

static void log_recv_error(int status, int fd) {
    if (status == -1) {
        char *msg = mx_sprintf("Client from socket %d disconnected\n", fd);
        logger_info(msg);
        free(msg);
    } else if (status == -2) {
        char *msg = mx_sprintf("Error receiving data from socket %d\n", fd);
        logger_error(msg);
        free(msg);
    } else if (status == -3){
        char *msg = mx_sprintf("Wrong data size format from socket %d\n", fd);
        logger_error(msg);
        free(msg);
    } else {
        char *msg = mx_sprintf("Unknown error on socket %d\n", fd);
        logger_error(msg);
        free(msg);
    }
}

static int receive_request(int fd, char **request) {
    int status = mx_receive_data(fd, request);
    if (status < 0) {
        log_recv_error(status, fd);
        if (*request) {
            free(*request);
            *request = NULL;
        }
    }
    return status;
}

static char *process_request(char *request, int fd) {
    char *msg = mx_sprintf("Received data from socket %d\n", fd);
    logger_error(msg);
    free(msg);

    char *response = mx_handle_request(request);
    if (!response) {
        msg = mx_sprintf("Socket %d: request handling error\n", fd);
        logger_debug(msg);
        free(msg);
        return NULL;
    }
    msg = mx_sprintf("Can send response to the socket %d", fd);
    logger_debug(msg);
    free(msg);
    return response;
}

static int send_response(char *response, int fd) {
    logger_debug("mx_handle_connection: send_response");
    logger_debug(response);
    int status = mx_send_data(fd, response);
    if (status < 0) {
        char *msg = mx_sprintf("Error sending data to the socket %d\n", fd);
        logger_error(msg);
        free(msg);
    } else {
        char *msg = mx_sprintf("Response sent to the socket %d", fd);
        logger_info(msg);
        free(msg);
    }
    return status;
}

void *mx_handle_connection(void *data) {
    t_client_info *info = (t_client_info *)data;

    while (1) {
        char *request = NULL;
        int status = receive_request(info->fd, &request);
        if (status < 0) if (request) free(request);
        if (status == -1) break;
        if (status < 0) continue;
        char *response = process_request(request, info->fd);
        if (request) free(request);
        status = send_response(response, info->fd);
        free(response);
        if (status < 0) break;
    }
    finalize_client(info);
    pthread_exit(NULL);
}
