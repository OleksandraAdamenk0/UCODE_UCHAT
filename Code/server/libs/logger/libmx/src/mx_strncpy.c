#include "libmx.h"

/**
 * @NAME Copy them all
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard libc function strncpy.
 * @note \n
 */

char *mx_strncpy(char *dst, const char *src, int len) {
    char *d = dst;

    const char *s = src;
    while (len != 0) {
        if ((*d++ = *s++) == '\0') {
            while (--len != 0) *d++ = '\0';
            break;
        }
        len--;
    }
    return dst;
}
