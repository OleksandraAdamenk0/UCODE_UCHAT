#include "libmx.h"

/**
* @NAME Decimal to hex
* @DESCRIPTION Create a function that converts an unsigned long number
 * into a hexadecimal string.
* @RETURN Returns the number converted to a hexadecimal string.
* @note \n
*/

char *mx_nbr_to_hex(unsigned long nbr) {
    if (nbr == 0) return mx_char_to_str('0');
    unsigned long size = 0;
    char str[256];
    char variants[] = "0123456789abcdef";
    for (; nbr > 0 ; nbr /= 16) str[size++] = variants[nbr % 16];
    char *result = mx_strnew((int)size);
    if (result == NULL) return NULL;
    for (unsigned long i = 0; i < size; i++) result[i] = str[size - i - 1];
    result[size] = '\0';
    return result;
}
