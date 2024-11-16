#ifndef CLIENT_H
#define CLIENT_H

#include "libmx.h"
// #include "logger.h"
#include "sqlite3.h"

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080

int create_socket();
int connect_to_server(int sockfd, const char *ip, int port);
void close_connection(int sockfd);
int send_data(int sockfd, const char *data);
int receive_data(int sockfd, char *buffer, int size);

#endif
