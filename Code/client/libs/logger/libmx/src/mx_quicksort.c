#include "libmx.h"

static void swap_qs(char **a, char **b) {
    if (a == NULL || b == NULL || *a == NULL || *b == NULL) return;
    char *temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @NAME Quick sort
 * @DESCRIPTION Create a function that: \n
 * - sorts an array of strings by their lengths in ascending order \n
 * - uses the quick sort algorithm.
 * Select the middle element of the array
 * as the center. \n
 * You must not check the validity of left and right.
 * @RETURN - returns the number of swaps. \n
 * - returns -1 if arr does not exist
 * @note \n
 */

int mx_quicksort(char **arr, int left_index, int right_index) {
    if (!arr) return -1;
    int swaps = 0;
    int li = left_index;
    int ri = right_index;
    if (li == ri) return swaps;
    char *pivot = arr[(li + ri) / 2];
    if (!pivot) return -1;
    while (li <= ri) {
        if (!arr[li] || !arr[ri]) return -1;
        while (mx_strlen(arr[li]) < mx_strlen(pivot)) li++;
        while (mx_strlen(arr[ri]) > mx_strlen(pivot)) ri--;
        if (li <= ri) {
            if (li != ri && mx_strlen(arr[li]) != mx_strlen(arr[ri])) {
                swap_qs(&arr[li], &arr[ri]);
                swaps++;
            }
            li++;
            ri--;
        }
    }
    if (left_index < ri) swaps += mx_quicksort(arr, left_index, ri);
    if (li < right_index) swaps += mx_quicksort(arr, li, right_index);
    return swaps;
}
