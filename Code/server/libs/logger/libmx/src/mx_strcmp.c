#include "libmx.h"

/**
 * @NAME Compare strings
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard libc function strcmp.
 * @note \n
 */

int mx_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        ++s1;
        ++s2;
    }
    return *s1 - *s2;
}
