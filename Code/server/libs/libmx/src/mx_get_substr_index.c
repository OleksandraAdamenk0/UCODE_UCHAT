#include "libmx.h"

/**
 * @NAME Get substring index
 * @DESCRIPTION Create a function that finds the index of a substring.
 * @RETURN returns the index of the first character of sub in str \n
 * returns -1 if sub is not found in str\n
 * returns -2 if str or sub does not exist
 * @note \n
 */

int mx_get_substr_index(const char *str, const char *sub) {
    if (!str || !sub) return -2;
    char *p_sub = mx_strstr(str, sub);
    if (!p_sub || mx_strlen(str) == 0 || mx_strlen(sub) == 0) return -1;
    return (int)(p_sub - str);
}
