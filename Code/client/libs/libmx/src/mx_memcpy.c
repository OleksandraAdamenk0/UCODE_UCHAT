#include "libmx.h"

/**
 * @NAME Copy memory
 * @DESCRIPTION Create a function that  has the same behavior
 * as the standard libc function memcpy. \n
 * @note \n
 */

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    while (n--) *d++ = *s++;
    return dst;
}
