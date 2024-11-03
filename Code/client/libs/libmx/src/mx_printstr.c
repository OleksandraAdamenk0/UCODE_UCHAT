#include "libmx.h"

/**
 * @NAME Print string
 * @DESCRIPTION Create a function that
 * outputs a string of characters to the standard output.
 * @note \n
 */

void mx_printstr(const char *s) {
    if (s) write(1, s, mx_strlen(s));
}
