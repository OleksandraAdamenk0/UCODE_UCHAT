#include "libmx.h"

/**
 * @NAME For each
 * @DESCRIPTION Create a function that applies the function f
 * for each element of the array arr given size.
 * @note \n
 */

void mx_foreach(int *arr, int size, void (*f)(int)) {
    if (arr == NULL || f == NULL || size < 1) return;
    for (int i = 0; i < size; ++i) f(arr[i]);
}
