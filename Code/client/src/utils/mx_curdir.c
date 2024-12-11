//
// Created by oleksandra on 04/12/24.
//

#include "utils.h"
#include <stdlib.h>

char *mx_curdir() {
    char *real_path = realpath(".", NULL);
    if (!real_path) return NULL;
    char *currdir = mx_sprintf("file://%s", real_path);
    free(real_path);
    return currdir;
}
