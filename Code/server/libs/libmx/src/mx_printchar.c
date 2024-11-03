#include "libmx.h"

/**
 * @NAME Print character
 * @DESCRIPTION Create a function that outputs a single character to the standard output.
 * @note \n
 */

void mx_printchar(char c) {
    write(1, &c, 1);
}
