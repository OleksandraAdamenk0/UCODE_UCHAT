#include "libmx.h"

static int error_exit(char **lineptr, int code) {
    mx_strdel(lineptr);
    return code;
}

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    if (fd < 0 || !lineptr || buf_size <= 0) return -2;

    size_t number = 0;
    char buff;
    ssize_t bytes;
    char *new_lineptr = NULL;

    if (!(*lineptr = mx_strnew(buf_size))) return -2;

    while ((bytes = read(fd, &buff, 1)) > 0) {
        if (buff == delim) break;
        (*lineptr)[number++] = buff;

        if (number >= buf_size) {
            buf_size *= 2;
            new_lineptr = mx_realloc(*lineptr, buf_size);
            if (!new_lineptr) error_exit(lineptr, -2);
            *lineptr = new_lineptr;
        }
    }
    if (bytes == -1) error_exit(lineptr, -2);
    if (bytes == 0 && number == 0) error_exit(lineptr, -1);
    (*lineptr)[number] = '\0';
    return number;
}

