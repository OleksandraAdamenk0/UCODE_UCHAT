//
// Created by oleksandra on 01/12/24.
//
#include "gui.h"
#include "libmx.h"

char *mx_create_js_func_call(char *name, char *argument) {
    char *cmd1 = mx_strjoin(name, "('");
    if (!cmd1) return NULL;
    char *cmd2 = mx_strjoin(cmd1, argument);
    free(cmd1);
    if (!cmd2) return NULL;
    char *cmd = mx_strjoin(cmd2, "');");
    free(cmd2);
    return cmd;
}
