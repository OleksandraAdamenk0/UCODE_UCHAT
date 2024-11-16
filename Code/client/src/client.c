#include "client.h"

int create_socket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        // mx_printerr("Error creating socket");
        return -1;
    }
    return sockfd;
}

int connect_to_server(int sockfd, const char *ip, int port) {
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        return -1;
    }
    return 0;
}

void close_connection(int sockfd) {
    close(sockfd);
}

int send_data(int sockfd, const char *data) {
    return send(sockfd, data, mx_strlen(data), 0);
}

int receive_data(int sockfd, char *buffer, int size) {
    return recv(sockfd, buffer, size, 0);
}
