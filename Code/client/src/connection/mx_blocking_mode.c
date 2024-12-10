//
// Created by oleksandra on 04/12/24.
//

#include "connection.h"
#include "logger.h"

#include <sys/socket.h>
#include <arpa/inet.h>

int mx_blocking_mode(int sockfd, struct sockaddr_in svr_addr) {
    logger_warn("mx_blocking_mode: running");
    if (connect(sockfd, (struct sockaddr *)&svr_addr, sizeof(svr_addr)) < 0) {
        logger_fatal("mx_blocking_mode: Failed to connect to the server");
        return -1;
    }
    return 0;
}
