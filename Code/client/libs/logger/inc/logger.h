//
// Created by aleksa on 11/2/24.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#include "libmx.h"

int logger_init(char *config_path);

int logger_debug(char *msg);

int logger_info(char *msg);

int logger_warn(char *msg);

int logger_error(char *msg);

int logger_fatal(char *msg);

void logger_close();

#endif //LOGGER_H
