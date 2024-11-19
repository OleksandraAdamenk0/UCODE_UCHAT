#ifndef CONNECTION_HANDLING_H
#define CONNECTION_HANDLING_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

int create_socket();
int connect_to_server(int sockfd, const char *ip, int port);
void close_connection(int sockfd);

#endif
