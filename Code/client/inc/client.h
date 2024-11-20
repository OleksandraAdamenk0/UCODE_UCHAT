//
// Created by oleksandra on 17/11/24.
//

#ifndef UCODE_UCHAT_MAIN_CLIENT_H
#define UCODE_UCHAT_MAIN_CLIENT_H

#include "libmx.h"
#include "logger.h"

extern int port;
extern char *ip;

int mx_init(int argc, const char * argv[]);

int mx_open_connection();
void mx_close_connection(int sockfd);

void debug_send(int fd, char *str);

#endif //UCODE_UCHAT_MAIN_CLIENT_H
