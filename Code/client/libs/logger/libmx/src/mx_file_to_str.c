#include "libmx.h"

static int count_len(const char *file) {
    int fd = open(file, O_RDONLY);
    if (fd < 0) return -1;

    int len = 0;
    char buf;
    ssize_t bread;

    while ((bread = read(fd, &buf, 1)) > 0) len++;
    if (bread < 0) {
        close(fd);
        return -1;
    }
    if (close(fd) < 0) return -1;
    return len;
}

static char *logic(const char *file, int len) {
    char *result = mx_strnew(len);
    if (result == NULL) return NULL;
    int fd = open(file, O_RDONLY);
    if (fd < 0) {
        free(result);
        return NULL;
    }
    if (read(fd, result, len) < len) {
        free(result);
        close(fd);
        return NULL;
    }
    if (close(fd) < 0) {
        free(result);
        return NULL;
    }
    return result;
}

/**
 * @NAME File to string
 * @DESCRIPTION Create a function that: \n
 * takes a filename as a parameter \n
 * reads data fom the file into a sting
 * @RETURN returns a NULL-terminated string \n
 * returns NULL in case of any errors
 * @note \n
 */

char *mx_file_to_str(const char *file) {
    if (file == NULL) return NULL;
    int len = count_len(file);
    if (len == 0) return mx_strnew(0);
    if (len < 0) return NULL;
    return logic(file, len);
}
