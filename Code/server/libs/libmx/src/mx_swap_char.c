#include "libmx.h"

/**
 * @NAME Swap characters
 * @DESCRIPTION Create a function that swaps the characters
 * of a string using pointers. Do nothing if s1 or s2 does not exist.
 * @note \n
 */

void mx_swap_char(char *s1, char *s2) {
    if (s1 == NULL || s2 == NULL || s1 == s2) return;
    char temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}
