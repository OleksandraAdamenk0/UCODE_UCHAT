//
// Created by aleksa on 11/2/24.
//

#ifndef SERVER_H
#define SERVER_H

#include <stdlib.h>

#include "libmx.h"
#include "logger.h"

int mx_init_server(int argc, const char * argv[]);

char *handle_request(const char *request_str);

#endif //SERVER_H
