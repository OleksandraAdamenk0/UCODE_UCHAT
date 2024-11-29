//
// Created by oleksandra on 17/11/24.
//

#ifndef UCODE_UCHAT_MAIN_CONNECTION_H
#define UCODE_UCHAT_MAIN_CONNECTION_H

#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct s_client_info {
    int *fd;
    struct sockaddr_in addr;
} t_client_info;

extern int svr_fd;
extern struct sockaddr_in svr_addr;
extern volatile sig_atomic_t server_running;

void mx_handle_signal(int sig);
void *mx_handle_connection(void *p_client_info);
void mx_finalize_client(t_client_info *info);

int mx_send_data(int fd, char *response);
int mx_receive_data(int fd, char **request);

#endif //UCODE_UCHAT_MAIN_CONNECTION_H
