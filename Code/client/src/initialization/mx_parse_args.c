//
// Created by oleksandra on 17/11/24.
//

#define ARGS_AMOUNT 3

#include "client.h"
#include "connection.h"
#include "libmx.h"

static int is_ip(const char *str) {
    int dots = mx_count_substr(str, ".");
    if (dots != 3) return -1;

    char **parts = mx_strsplit(str, '.');
    for (int i = 0; i < 4; ++i) {
        if (mx_is_numeric(parts[i]) == 0) {
            for (int j = i; j < 4; ++j) free(parts[i]);
            free(parts);
            return -1;
        }
        int num = mx_atoi(parts[i]);
        if (num < 0 || num > 255) {
            for (int j = i; j < 4; ++j) free(parts[i]);
            free(parts);
            return -1;
        }
        free(parts[i]);
    }
    free(parts);
    return 0;
}

static int is_port(const char *str) {
    if (mx_is_numeric(str) == false) return -1;
    int num = mx_atoi(str);
    if (num < 0 || num > 65535) return -1;
    return 0;
}

#include "logger.h"

int mx_parse_args(int argc, const char *argv[], int *port, char **ip) {
    *port = -1;
    *ip = NULL;

    if (argc != ARGS_AMOUNT) return -1;
    for (int i = 1; i < ARGS_AMOUNT; ++i) {
        if (is_port(argv[i]) == 0 && *port == -1) *port = mx_atoi(argv[i]);
        else if (is_ip(argv[i]) == 0 && *ip == NULL) *ip = mx_strdup(argv[i]);
        else return -1;
    }
    return 0;
}