//
// Created by oleksandra on 17/11/24.
//

#ifndef UCODE_UCHAT_MAIN_INITIALIZATION_H
#define UCODE_UCHAT_MAIN_INITIALIZATION_H

#define LOGGER_CONFIG "client/logger.conf"

#include <stdlib.h>
#include "libmx.h"

typedef struct {
    int port;
    char *ip;
} arguments;


arguments *mx_parse_args(int argc, const char *argv[]);


#endif //UCODE_UCHAT_MAIN_INITIALIZATION_H