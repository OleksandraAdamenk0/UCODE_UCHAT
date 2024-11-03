#include "libmx.h"

/**
 * @NAME Binary search
 * @DESCRIPTION Create a function that: \n
 * - searches the string s in the array arr
 * with the given size of array \n
 * - uses the binary search algorithm assuming that
 * the input array has already been sorted in a lexicographical order
 * @RETURN - returns the index of the found string in the array \n
 * - returns -1 in case of errors
 * or if the string has not been found \n
 * - assigns the number of required iterations to the count pointer
 * @note \n
 */

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    if (count) *count = 0;
    if (!arr || !s || size <= 0 || !count) return -1;
    int left = 0;
    int right = size - 1;
    int mid;
    while (right >= left) {
        (*count)++;
        mid = (left + right) / 2;
        int similarity = mx_strcmp(arr[mid], s);
        if (similarity == 0) return mid;
        else if (similarity < 0) left = mid + 1;
        else right = mid - 1;
    }
    *count = 0;
    return -1;
}
