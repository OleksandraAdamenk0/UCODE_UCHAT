//
// Created by oleksandra on 05/12/24.
//
#include "initialization.h"
#include "libmx.h"

int mx_parse_args(int argc, const char *argv[], int *port) {
    if (argc != 2 || !mx_is_numeric(argv[1])) return -1;
    *port = mx_atoi(argv[1]);
    if (*port < 0 || *port > 65535) return -1;
    return 0;
}
