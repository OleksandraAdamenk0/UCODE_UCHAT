//
// Created by aleksa on 11/2/24.
//

#ifndef SERVER_H
#define SERVER_H

#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "libmx.h"
#include "logger.h"

int mx_init_server(int argc, const char * argv[]);
void *mx_handle_client(void *client_socket);


#endif //SERVER_H
