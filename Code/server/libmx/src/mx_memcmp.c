#include "libmx.h"

/**
 * @NAME Compare memory
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard stdlib function memcmp. \n
 * @note \n
 */

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    const unsigned char *p1 = (const unsigned char *) s1;
    const unsigned char *p2 = (const unsigned char *) s2;
    for (size_t i = 0; i < n; ++i) if (p1[i] != p2[i]) return p1[i] - p2[i];
    return 0;
}
