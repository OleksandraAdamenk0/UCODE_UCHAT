//
// Created by oleksandra on 17/11/24.
//

#include "server.h"
#include "connection.h"

static int set_nonblocking_mode(int fd) {
    int flags = fcntl(svr_fd, F_GETFL, 0);
    if (flags == -1 || fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        logger_fatal("Failed to set non-blocking mode for server socket\n");
        return -1;
    }
    return 0;
}

static t_client_info *accept_client() {
    int *cnt_fd = malloc(sizeof(int));
    if (cnt_fd == NULL) {
        logger_warn("Memory allocation failed for cnt_fd\n");
        return NULL;
    }

    struct sockaddr_in cnt_addr;
    socklen_t addrlen = sizeof(cnt_addr);
    *cnt_fd = accept(svr_fd, (struct sockaddr *)&cnt_addr,&addrlen);

    if (*cnt_fd < 0) {
        free(cnt_fd);
        // not an error (no connections)
        if (errno == EAGAIN || errno == EWOULDBLOCK) return NULL;
        // error
        logger_warn("An attempt to accept an incoming connection failed\n");
        return NULL;
    }

    t_client_info *info = malloc(sizeof(t_client_info));
    if (info == NULL) {
        logger_warn("Memory allocation failed for client info\n");
        close(*cnt_fd);
        free(cnt_fd);
        free(info);
        return NULL;
    }

    info->fd = cnt_fd;
    info->addr = cnt_addr;
    return info;
}

static int create_client_thread(t_client_info *info) {
    pthread_t client_thread;
    if (pthread_create(&client_thread, NULL, mx_handle_connection, info) != 0) {
        logger_warn("Error occurred while creating a thread\n");
        close(*(info->fd));
        free(info->fd);
        free(info);
        return -1;
    }
    pthread_detach(client_thread);
    return 0;
}

int mx_accept_connections() {
    // non-blocking mode for server socket
    if (set_nonblocking_mode(svr_fd) < 0) return -1;
    logger_info("Server starting receiving connections\n");

    while (server_running) {
        t_client_info *cnt_info = accept_client();
        if (!cnt_info) {
            if (!server_running) break;
            usleep(100000);
            continue;
        }

        logger_info("New incoming connection accepted.\n");

        if (create_client_thread(cnt_info) != 0)
            logger_warn("Failed to handle client connection\n");
    }
    logger_info("Server stopped receiving connections\n");
    return 0;
}
