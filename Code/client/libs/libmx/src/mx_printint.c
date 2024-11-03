#include "libmx.h"

/**
 * @NAME Print integer
 * @DESCRIPTION Create a function that
 * outputs integer values to the standard output.
 * @note \n
 */

void mx_printint(int n) {
    if (n == 0) mx_printchar('0');
    else {
        long long int nc = (long long int)n;
        if (nc < 0) mx_printchar('-');
        if (nc < 0) nc = -nc;
        char buffer[64];
        int counter = 0;
        for (; nc > 0 ; nc /= 10) buffer[counter++] = (char)((nc % 10) + '0');
        for (int i = counter - 1; i >= 0; --i) mx_printchar(buffer[i]);
    }
}
