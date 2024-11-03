#include "libmx.h"

/**
 * @NAME New string
 * @DESCRIPTION Create a function that:\n
 * allocates memory for a string of a specific size and one additional byte
 * for the terminating '\0'\n
 * initializes each character with '\0'
 * @RETURN returns the string of a specific\n
 * returns NULL if creation fails
 * @note \n
 */

char *mx_strnew(const int size) {
    if (size < 0) return NULL;
    char* result = malloc(size + 1 * sizeof(char));
    if (result == NULL) return NULL;
    mx_memset(result, '\0', size + 1);
    return result;
}
