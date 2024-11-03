#include "libmx.h"

/**
 * @NAME Bubble sort
 * @DESCRIPTION Create a function that: \n
 * - sorts an array of strings in place in lexicographical order \n
 * - uses the bubble sort algorithm
 * @RETURN - Returns the number of swap operations.
 * @note \n
 */

int mx_bubble_sort(char **arr, int size) {
    int swaps = 0;
    int swapped = 1;
    for (int i = 0; i < size - 1 && swapped; i++) {
        // if (arr[i] == NULL) return -1;
        swapped = 0;
        for (int j = 0; j < size - i - 1; j++) {
            // if (arr[j] == NULL) return -1;
            if (mx_strcmp(arr[j], arr[j + 1]) > 0) {
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps++;
                swapped = 1;
            }
        }
    }
    return swaps;
}
