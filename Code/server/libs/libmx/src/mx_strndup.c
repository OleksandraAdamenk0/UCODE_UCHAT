#include "libmx.h"

static size_t size_t_strlen(const char *s) {
    size_t len = 0;
    for (; *s != '\0'; s++) len++;
    return len;
}

static char *size_t_strnew(const size_t size) {
    char* result = malloc(size + 1);
    if (result == NULL) return NULL;
    char* copy = result;
    for (size_t i = 0; i <= size; i++) *copy++ = '\0';
    return result;
}

/**
 * @NAME Duplicate part of string
 * @DESCRIPTION Create a function that has the same behavior
 *  as the standard libc function strndup.
 * @note \n
 */

char *mx_strndup(const char *s1, size_t n) {
    size_t len = (size_t)size_t_strlen(s1);
    len = (len > n)? n: len;
    char *res = size_t_strnew(len);
    if (res) mx_memcpy(res, s1, len);
    return res;
}
