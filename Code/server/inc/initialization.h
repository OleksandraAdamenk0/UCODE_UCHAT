//
// Created by aleksa on 11/2/24.
//

#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#define LOGGER_CONFIG "server/logger.conf"

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "libmx.h"

typedef struct s_arguments {
    int port;
    char *ip;
} t_arguments;

t_arguments *mx_parse_args(int argc, const char *argv[]);
int mx_create_daemon();

#endif //INITIALIZATION_H
