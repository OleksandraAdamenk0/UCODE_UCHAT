#include "libmx.h"

/**
 * @NAME Fill memory
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard libc function memset.
 * @note \n
 */

void *mx_memset(void *b, int c, size_t len) {
    unsigned char *ptr = (unsigned char *)b;
    unsigned char value = (unsigned char)c;
    for (size_t i = 0; i < len; ++i) ptr[i] = value;
    return b;
}
