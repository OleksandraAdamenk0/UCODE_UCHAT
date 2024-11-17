//
// Created by aleksa on 11/2/24.
//

#ifndef SERVER_H
#define SERVER_H

#include <stdlib.h>
#include <netinet/in.h>

#include "libmx.h"
#include "logger.h"

extern int port;
extern char *ip;
extern int svr_fd;
extern struct sockaddr_in svr_addr;

int mx_init_server(int argc, const char * argv[]);

char *mx_handle_request(const char *request_str);

int mx_open_connection();
int mx_accept_connections();

#endif //SERVER_H
