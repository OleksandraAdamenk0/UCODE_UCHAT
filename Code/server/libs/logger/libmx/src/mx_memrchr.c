#include "libmx.h"

/**
 * @NAME Locate byte from end
 * @DESCRIPTION Create a function mx_memrchr,
 * which is similar to the function mx_memchr,
 * except that it searches in the opposite direction
 * from the end of the bytes n points to s
 * instead of directly from the beginning.\n
 * @note \n
 */

void *mx_memrchr(const void *s, int c, size_t n){
    const unsigned char *s1 = (unsigned char *) s;
    unsigned char c1 = (unsigned char) c;
    for (size_t i = n; i > 0; --i)
        if (s1[i - 1] == c1) return (void *) (s1 + i - 1);
    return NULL;
}
