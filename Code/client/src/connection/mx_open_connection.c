//
// Created by oleksandra on 17/11/24.
//

#include "connection.h"
#include "logger.h"
#include "libmx.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

static int create_socket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        logger_error("mx_open_connection: Failed to create socket");
        return -1;
    }
    logger_debug("mx_open_connection: Socket was created successfully");
    return sockfd;
}

static struct sockaddr_in create_address() {
    struct sockaddr_in addr;
    mx_memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    return addr;
}

static int convert_ip(char *ip, struct sockaddr_in *addr) {
    logger_debug(ip);
    if (inet_pton(AF_INET, ip, &addr->sin_addr) <= 0) {
        if (errno == EAFNOSUPPORT)
            logger_error("convert_ip_to_bin: Address family not supported");
        else logger_error("convert_ip_to_bin: Invalid IP address");
        return -1;
    }
    return 0;
}

static int setup_non_blocking_mode(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) return -1;
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) return -1;
    return 0;
}

static int setup_blocking_mode(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) {
        logger_error("Failed to get socket flags\n");
        return -1;
    }

    flags &= ~O_NONBLOCK;
    if (fcntl(sockfd, F_SETFL, flags) == -1) {
        logger_error("Failed to set socket to blocking mode\n");
        return -1;
    }

    logger_debug("Socket is set to blocking mode\n");
    return 0;

}

int mx_open_connection() {
    int result = create_socket();
    if (result < 0) return -1;

    struct sockaddr_in server_addr = create_address();
    if (convert_ip(ip, &server_addr) < 0) {
        close(fd);
        return -1;
    }

    // set up non-blocking mode to get control back to the program
    // without waiting for connect to be executed
    if (setup_non_blocking_mode(result) < 0)
        return mx_blocking_mode(result, server_addr);

    int status = mx_non_blocking_mode(result, server_addr);
    if (setup_blocking_mode(result) < 0)
        logger_warn("mx_open_connection: Failed to restore blocking mode");

    if (status < 0) return status;
    return result;
}
