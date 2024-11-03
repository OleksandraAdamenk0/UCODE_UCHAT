#include "libmx.h"

/**
 * @NAME Locate block of bytes
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard libc function memmem.\n
 * @note \n
 */
void *mx_memmem(const void *big, size_t big_len,
                const void *little, size_t little_len) {
    if (big_len < little_len) return NULL;

    const unsigned char *big_ptr = big;
    const unsigned char *little_ptr = little;

    for (size_t i = 0; i < big_len; i++)
        if (mx_memcmp(big_ptr + i, little_ptr, little_len - 1) == 0)
            return (void*)(big_ptr + i);

    return NULL;
}
