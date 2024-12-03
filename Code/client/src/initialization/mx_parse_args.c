//
// Created by oleksandra on 17/11/24.
//

#include "initialization.h"
#include "libmx.h"

static int is_ip(const char *str) {
    int dots = mx_count_substr(str, ".");
    if (dots != 3) return -1;

    char **parts = mx_strsplit(str, '.');
    for (int i = 0; i < 4; ++i) {
        if (mx_is_numeric(parts[i]) == false) {
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

t_arguments *mx_parse_args(int argc, const char *argv[]) {
    // program name, ip_address, port
    if (argc != 3) return NULL;

    t_arguments *result = malloc(sizeof(t_arguments));
    result->port = -1;
    result->ip = NULL;

    for (int i = 1; i < 3; ++i) {
        if (!result->ip && is_ip(argv[i]) == 0)
            result->ip = mx_strdup(argv[i]);
        else if (result->port < 0 && is_port(argv[i]) == 0)
            result->port = mx_atoi(argv[i]);
        else {
            free(result);
            return NULL;
        }
    }

    return result;
}
