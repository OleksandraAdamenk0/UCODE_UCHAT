#include "libmx.h"

/**
 * @NAME Integer to ASCII
 * @DESCRIPTION Create a function that takes an integer
 * and converts it to a string.
 * @RETURN Returns the number as a NULL-terminated string.
 * @note \n
 */

char *mx_itoa(int number) {
    if (number == 0) return mx_char_to_str('0');
    char str[64];
    int size = 0;
    int minus = 0;
    long long int copy = (long long int) number;
    if (number < 0) minus = 1;
    if (number < 0) copy = -copy;
    for (; copy > 0; copy /= 10) str[size++] = (char)((copy % 10) + '0');
    if (minus) str[size++] = '-';
    char *result = mx_strnew(size);
    if (!result) return NULL;
    for (int i = 0; i < size; i++) result[i] = str[size - i - 1];
    return result;
}
