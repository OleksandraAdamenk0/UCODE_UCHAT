#include "libmx.h"

/**
 * @NAME Additional
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard libc function strncmp.
 * @note \n
 */

int mx_strncmp(const char *s1, const char *s2, int n) {
    for (; n > 0 && (*s1 || *s2); n--, s1++, s2++)
        if (*s1 != *s2) return (unsigned char)*s1 - (unsigned char)*s2;
    return 0;
}
