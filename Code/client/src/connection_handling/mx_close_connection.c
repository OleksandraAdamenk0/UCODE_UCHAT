#include "connection_handling.h"

void close_connection(int sockfd) {
    close(sockfd);
}
