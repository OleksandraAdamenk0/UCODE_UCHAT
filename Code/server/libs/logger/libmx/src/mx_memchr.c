#include "libmx.h"

/**
 * @NAME Locate byte from start
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard stdlib function memchr. \n
 * @note \n
 */

void *mx_memchr(const void *s, int c, size_t n) {
    const unsigned char *s1 = (unsigned char *) s;
    unsigned char c1 = (unsigned char) c;
    for (size_t i = 0; i < n; ++i) if (s1[i] == c1) return (void *) (s1 + i);
    return NULL;
}
