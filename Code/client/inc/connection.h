//
// Created by oleksandra on 17/11/24.
//

#ifndef UCODE_UCHAT_MAIN_CONNECTION_H
#define UCODE_UCHAT_MAIN_CONNECTION_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/select.h>

extern int fd;
extern int port;
extern char *ip;

#endif //UCODE_UCHAT_MAIN_CONNECTION_H
