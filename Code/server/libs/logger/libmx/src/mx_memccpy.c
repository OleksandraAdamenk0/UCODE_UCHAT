#include "libmx.h"

/**
 * @NAME Copy memory to ...
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard stdlib function memccpy.\n
 * @note \n
 */

void *mx_memccpy(void *restrict dst,
                 const void *restrict src, int c, size_t n) {
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    unsigned char stop_char = (unsigned char)c;
    while (n--) {
        *d++ = *s;
        if (*s == stop_char) return d;
        s++;
    }
    return NULL;
}
