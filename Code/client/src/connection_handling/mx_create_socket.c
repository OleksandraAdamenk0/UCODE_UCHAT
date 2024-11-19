#include "connection_handling.h"

int create_socket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        // mx_printerr("Error creating socket");
        return -1;
    }
    return sockfd;
}
