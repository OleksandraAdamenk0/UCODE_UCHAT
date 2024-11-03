#include "libmx.h"

/**
 * @NAME Non-overlapping memory copy
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard libc function memmove.\n
 * @note \n
 */

void *mx_memmove(void *dst, void *src, size_t len) {
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    if (d < s) for (size_t i = 0; i < len; ++i) d[i] = s[i];
    else for (size_t i = len; i > 0; --i) d[i - 1] = s[i - 1];
    return dst;
}
