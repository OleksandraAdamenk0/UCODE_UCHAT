//
// Created by oleksandra on 17/11/24.
//

#include "server.h"
#include "connection.h"

int mx_accept_connections() {
    // non-blocking mode for server socket
    int flags = fcntl(svr_fd, F_GETFL, 0);
    fcntl(svr_fd, F_SETFL, flags | O_NONBLOCK);

    while (server_running) {
        int *cnt_fd = malloc(sizeof(int));
        socklen_t addrlen = sizeof(svr_addr);

        *cnt_fd = accept(svr_fd, (struct sockaddr *)&svr_addr, (socklen_t *)&addrlen);
        if ((*cnt_fd) < 0) {
            // not an error (no connections)
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                if (server_running == 0) break;
                free(cnt_fd);
                usleep(100000);  // small delay to save server resources
                continue;
            }
            logger_warn("attempt to accept an incoming connection failed\n");
            free(cnt_fd);
            continue;
        }
        logger_info("connection accepted.\n");

        // Create a new thread for the client
        pthread_t client_thread;
        if (pthread_create(&client_thread, NULL, mx_handle_connection, cnt_fd) != 0) {
            logger_warn("error occurred while creating a thread\n");
            free(cnt_fd);
            continue;
        }

        // Separate the thread so that it terminates on its own
        pthread_detach(client_thread);
    }
    logger_info("server stopped receiving connections\n");
    return 0;
}