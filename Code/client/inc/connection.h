//
// Created by oleksandra on 04/12/24.
//

#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include <netinet/in.h>
#include <pthread.h>

extern int fd;
extern int port;
extern char *ip;

void *mx_connection_thread(void *arg);
int mx_open_connection();
int mx_blocking_mode(int sockfd, struct sockaddr_in svr_addr);
int mx_non_blocking_mode(int sockfd, struct sockaddr_in svr_addr);

int mx_send_data(char *data);
int mx_receive_data(char **data);

#endif //CLIENT_CONNECTION_H
