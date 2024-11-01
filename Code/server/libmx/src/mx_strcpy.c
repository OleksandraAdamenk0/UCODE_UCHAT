#include "libmx.h"

/**
 * @NAME Copy string
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard libc function strcpy.
 * @note \n
 */

char *mx_strcpy(char *dst, const char *src) {
    char *start = dst;

    while(*src) *dst++ = *src++;
    *dst = '\0';
    return start;
}
