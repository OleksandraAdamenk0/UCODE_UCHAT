#include "libmx.h"

/**
 * @NAME Count substrings
 * @DESCRIPTION Create a function that
 * counts the substrings sub in the string str.
 * @RETURN returns the count of sub in str. \n
 * returns 0 if sub is an empty string
 * @note \n
 */

int mx_count_substr(const char *str, const char *sub) {
    if (!str || !sub) return -1;
    if (sub[0] == '\0' || mx_strlen(sub) > mx_strlen(str)) return 0;
    char *p = (char *)str;
    int count = 0;

    for (;(p = mx_strstr(p, sub)) != NULL; p += mx_strlen(sub)) count++;
    return count;
}
