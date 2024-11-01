#include "libmx.h"

/**
 * @NAME Get character index
 * @DESCRIPTION Create a function that finds the index of the first occurrence
 * of the character c in a string str.
 * A string is a sequence of characters, excluding NULL in the end.
 * @RETURN returns the index of the first occurrence \n
 * returns -1 if no occurrence is found \n
 * returns -2 if the string does not exist
 * @note \n
 */

int mx_get_char_index(const char *str, char c) {
    if (!str) return -2;
    for (int i = 0; *str != '\0'; i++, str++) if (*str == c) return i;
    return -1;
}
