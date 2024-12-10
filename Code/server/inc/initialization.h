//
// Created by aleksa on 11/2/24.
//

#ifndef SERVER_INITIALIZATION_H
#define SERVER_INITIALIZATION_H

#define LOGGER_CONFIG "server/logger.conf"

int mx_parse_args(int argc, const char *argv[], int *port);
int mx_init_daemon();
int mx_init_db();

#endif //SERVER_INITIALIZATION_H
