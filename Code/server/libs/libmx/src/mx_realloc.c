#include "libmx.h"

/**
 * @NAME Reallocate memory
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard libc function realloc.\n
 * @note \n
 */

void *mx_realloc(void *ptr, size_t size)
{
    if (size <= 0 && ptr != NULL) {
        free(ptr);
        return NULL;
    }
    if (size > 0 && ptr == NULL) return malloc(size);

    void *new_ptr = NULL;
    size_t len = malloc_usable_size(ptr);

    if (len > size) {
        new_ptr = (void *)malloc(len);
        size = len;
    }
    else new_ptr = (void *)malloc(size);

    if (new_ptr == NULL) return NULL;

    new_ptr = mx_memmove(new_ptr, ptr, size);
    free(ptr);
    return new_ptr;
}
