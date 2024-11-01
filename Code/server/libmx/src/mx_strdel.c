#include "libmx.h"

/**
 * @NAME Delete string
 * @DESCRIPTION Create a function that: \n
 * takes a pointer to a string \n
 * fries string memory with free \n
 * sets the string to NULL
 * @note \n
 */

void mx_strdel(char **str) {
    if (str == NULL || *str == NULL) return;
    free(*str);
    *str = NULL;
}
