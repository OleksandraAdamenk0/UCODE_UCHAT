//
// Created by oleksandra on 17/11/24.
//

#include "server.h"
#include "connection.h"

int svr_fd;
struct sockaddr_in svr_addr;
volatile sig_atomic_t server_running;

int create_socket() {
    int fd;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) return -1;
    return fd;
}

struct sockaddr_in create_addr() {
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    return addr;
}

int mx_open_connection() {
    svr_fd = create_socket();
    if (svr_fd < 0) {
        logger_fatal("attempt to create server socket failed\n");
        return -1;
    }
    svr_addr = create_addr();

    if (bind(svr_fd, (struct sockaddr *)&svr_addr, sizeof(svr_addr)) < 0) {
        logger_fatal("attempt to bind server socket to the address failed\n");
        return -1;
    }

    if (listen(svr_fd, 0) < 0) {
        logger_fatal("attempt to start to listen "
                     "incoming connections failed\n");
        return -1;
    }

    server_running = 1;

    signal(SIGTERM, mx_handle_signal);
    signal(SIGINT, mx_handle_signal);

    return 0;
}