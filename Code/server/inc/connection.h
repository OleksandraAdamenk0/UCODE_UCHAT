//
// Created by oleksandra on 17/11/24.
//

#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#define MIN_DELAY 10000
#define MAX_DELAY 500000

#include <netinet/in.h>
#include <signal.h>

typedef struct s_client_info {
    int fd;
    struct sockaddr_in addr;
} t_client_info;

extern int svr_fd;
extern struct sockaddr_in svr_addr;
extern volatile sig_atomic_t server_running;

void mx_handle_signal(int sig);
void *mx_handle_connection(void *data);

int mx_receive_data(int fd, char **data);
int mx_send_data(int fd, char *data);

#endif //SERVER_CONNECTION_H
