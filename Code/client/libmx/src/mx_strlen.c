#include "libmx.h"

/**
 * @NAME String length
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard libc function strlen.
 * @note \n
 */

int mx_strlen(const char *s) {
    int len = 0;
    for (; *s != '\0'; s++) len++;
    return len;
}
