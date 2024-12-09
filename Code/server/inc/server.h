//
// Created by aleksa on 11/2/24.
//

#ifndef SERVER_H
#define SERVER_H

#include <stdlib.h>
#include <netinet/in.h>

#include "libmx.h"
#include "logger.h"
#include "connection.h"
#include "notifications.h"

extern int port;
extern char *ip;

// INITIALIZATION
int mx_init_server(int argc, const char * argv[]);
void mx_finalize_server();
//void *mx_handle_client(void *client_socket);

// REQUESTS
char *mx_handle_request(const char *request_str);

// CONNECTIONS
int mx_open_connection();
int mx_accept_connections();

// DATABASE
int mx_db_init();
void mx_db_finalize();

#endif //SERVER_H
