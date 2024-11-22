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

extern volatile sig_atomic_t server_running;

void mx_handle_signal(int sig);
void *mx_handle_connection(void *socket_ptr);

void send_data_with_length(int sock, char *data, size_t data_size);

#endif //UCODE_UCHAT_MAIN_CONNECTION_H
