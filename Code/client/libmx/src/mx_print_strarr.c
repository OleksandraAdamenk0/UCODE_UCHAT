#include "libmx.h"

/**
 * @NAME Print array of strings
 * @DESCRIPTION Create a function that outputs: \n
 * - an array of strings "arr" to the standard output with a delimiter
 * "delim" between the elements of an array \n
 * - nothing if "arr" or "delim" do not exist \n
 * - a newline at the end of the output "arr" must be NULL-terminated,
 * in other cases the behavior is undefined.
 * @note \n
 */

void mx_print_strarr(char **arr, const char *delim) {
    if (!arr || !delim) return;
    for (int i = 0; arr[i] != NULL; i++) {
        if (i > 0) mx_printstr(delim);
        mx_printstr(arr[i]);
    }
    mx_printstr("\n\0");
}
