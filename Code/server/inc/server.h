//
// Created by aleksa on 11/2/24.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

extern int port;
extern char *ip;

int mx_init_server(int argc, const char * argv[]);
void mx_finalize_server();
int mx_open_connection();
int mx_accept_connections();

#endif //SERVER_SERVER_H
