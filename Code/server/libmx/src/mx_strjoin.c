#include "libmx.h"

/**
 * @NAME Join strings
 * @DESCRIPTION Create a function that:\n
 *  concatenates strings s1 and s2 into a new string \n
 *  terminates the new string with '\0'
 *  @RETURN returns the string as a result of concatenation s1 and s2 \n
 *  returns the new copy of non-NULL parameter
 *  if one and only one of the parameters is NULL \n
 *  returns NULL if the concatenation fails
 * @note \n
 */

char *mx_strjoin(const char *s1, const char *s2) {
    if (s1 == NULL && s2 == NULL) return NULL;
    if (s1 == NULL) return mx_strdup(s2);
    if (s2 == NULL) return mx_strdup(s1);

    int size = mx_strlen(s1) + mx_strlen(s2);
    char *result = mx_strnew(size);
    if (result == NULL) return NULL;

    char *res_ptr = result;
    result = mx_strcpy(result, s1);
    result = mx_strcat(result, s2);
    return res_ptr;
}
