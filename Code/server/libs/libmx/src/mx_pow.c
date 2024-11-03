#include "libmx.h"

/**
 * @NAME Exponentiation
 * @DESCRIPTION Create a function that computes "n"
 * raised to the power of zero or a positive integer "pow".
 * @RETURN Returns the result of "n" to the power of "pow".
 * @note \n
 */

double mx_pow(double n, unsigned int pow) {
    double result = 1.0;
    for(; pow > 0; pow--) result *= n;
    return result;
}
