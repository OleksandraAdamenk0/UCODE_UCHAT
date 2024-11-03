#include "libmx.h"

char *mx_char_to_str(char c) {
    char *result = mx_strnew(1);
    if (!result) return NULL;
    result[0] = c;
    return result;
}
