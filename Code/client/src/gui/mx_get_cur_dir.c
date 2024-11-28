//
// Created by oleksandra on 26/11/24.
//
#include "gui.h"
#include "libmx.h"

char *mx_get_cur_dir() {
    char *currdir = g_get_current_dir();
    char *path = "file://";
    char *path1 = mx_strjoin(path, currdir);
    return path1;
}
