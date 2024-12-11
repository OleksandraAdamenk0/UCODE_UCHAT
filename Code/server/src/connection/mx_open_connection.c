//
// Created by oleksandra on 17/11/24.
//

#include "server.h"
#include "connection.h"
#include "logger.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdlib.h>

int svr_fd;
struct sockaddr_in svr_addr;
volatile sig_atomic_t server_running;

static int create_socket() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) logger_fatal("Failed to create socket\n");
    else logger_info("Server socket created\n");
    return fd;
}

struct sockaddr_in create_addr() {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    return addr;
}

static int bind_to_addr(int fd, struct sockaddr_in addr) {
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        logger_fatal("Failed to bind socket to the address\n");
        return -1;
    }
    logger_debug("Socket bound to address\n");
    return 0;
}

static int start_listening(int fd) {
    if (listen(fd, 0) < 0) {
        logger_fatal("Failed to start to listen incoming connections");
        return -1;
    }
    logger_debug("Server listening to incoming connections\n");
    return 0;
}

int mx_open_connection() {
    if ((svr_fd = create_socket()) < 0) return -1;
    svr_addr = create_addr();
    if (bind_to_addr(svr_fd, svr_addr) < 0) return -1;
    if (start_listening(svr_fd) < 0) return -1;

    server_running = 1;
    signal(SIGTERM, mx_handle_signal);
    signal(SIGINT, mx_handle_signal);

    logger_info("connection channel opened\n");
    return 0;
}
