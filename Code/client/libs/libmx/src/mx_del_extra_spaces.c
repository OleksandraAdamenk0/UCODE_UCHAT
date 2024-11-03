#include "libmx.h"

/**
 * @NAME Clean string
 * @DESCRIPTION Create a function that: \n
 * Takes a string and creates a new one from it without whitespace characters at the beginning
 * and/or at the end of the string. \n
 * Separates words in the new string with exactly one space character. \n
 * Frees all unused memory.
 * @RETURN returns a new created string; \n
 * returns NULL if the string str does not exist or string creation fails
 * @note \n
 */

char *mx_del_extra_spaces(const char *str) {
    if (!str) return NULL;
    char *s = mx_strtrim(str);
    if (s == NULL) return NULL;
    char *temp = mx_strnew(mx_strlen(s));
    int nl = 0;
    int sl = mx_strlen(s);
    while (*s) {
        if (!mx_isspace(*s)) temp[nl++] = *s;
        else if (!mx_isspace(temp[nl - 1])) temp[nl++] = ' ';
        s++;
    }
    char *result = mx_strnew(nl);
    mx_strncpy(result, temp, nl);
    free(temp);
    free(s - sl);
    return result;
}
