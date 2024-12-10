//
// Created by oleksandra on 04/12/24.
//
#include "utils.h"
#include "libmx.h"
#include <stdarg.h>

static char *process_format(char specifier, va_list args) {
    char *result = NULL;
    if (specifier == 'c') {
        char c = (char)va_arg(args, int);
        result = mx_char_to_str(c);
    } else if (specifier == 's') {
        char *s = va_arg(args, char *);
        result = mx_strdup(s);
    } else if (specifier == 'd') {
        int d = va_arg(args, int);
        result = mx_itoa(d);
    } else if (specifier == '%') {
        result = mx_strdup("%");
    } else {
        result = mx_char_to_str(specifier);
    }
    return result;
}

static char *process_string(const char *format, va_list args) {
    char *result = mx_strnew(0);
    char *temp = NULL;
    for (const char *ptr = format; *ptr; ++ptr) {
        if (*ptr == '%') {
            ++ptr;
            temp = process_format(*ptr, args);
            char *old_result = result;
            result = mx_strjoin(result, temp);
            mx_strdel(&old_result);
            mx_strdel(&temp);
        } else {
            char single_char[2] = {*ptr, '\0'};
            temp = mx_strdup(single_char);
            char *old_result = result;
            result = mx_strjoin(result, temp);
            mx_strdel(&old_result);
            mx_strdel(&temp);
        }
    }
    return result;
}

char *mx_sprintf(const char *format, ...) {
    if (!format) return NULL;

    va_list args;
    va_start(args, format);

    char *result = process_string(format, args);

    va_end(args);
    return result;
}
