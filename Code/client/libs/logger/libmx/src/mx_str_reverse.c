#include "libmx.h"

/**
 * @NAME Reverse string
 * @DESCRIPTION Create a function that  reverses a string using pointers.
 * Do nothing if a string does not exist.
 * @note \n
 */

void mx_str_reverse(char *s) {
    if (s == NULL) return;
    int len = mx_strlen(s);

    for (int i = 0; i < len / 2; ++i)
        mx_swap_char(s + i, s + len - i - 1);
}

