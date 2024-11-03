#include "libmx.h"

//static char *rem = NULL;

static int append(char **lineptr, const char *buffer, size_t buf_len, size_t *line_len) {
    *lineptr = realloc(*lineptr, *line_len + buf_len + 1);
    if (!*lineptr) return -1;
    mx_memcpy(*lineptr + *line_len, buffer, buf_len);
    *line_len += buf_len;
    (*lineptr)[*line_len] = '\0';
    return 0;
}

static int handle_rem(char **lineptr, char **remainder, size_t *line_len) {
    if (*remainder) {
        *lineptr = mx_strdup(*remainder);
        if (!*lineptr) return -1;
        *line_len = mx_strlen(*remainder);
        free(*remainder);
        *remainder = NULL;
        return 0;
    }
    *lineptr = malloc(1);
    if (!*lineptr) return -1;
    **lineptr = '\0';
    *line_len = 0;
    return 0;
}

static int find_del(char **lineptr, const char *buffer, size_t buf_size, char delim, char **remainder, size_t *line_len) {
    for (size_t i = 0; i < buf_size; ++i) {
        if (buffer[i] == delim) {
            size_t rem_start = i + 1;
            size_t rem_len = buf_size - rem_start;
            if (rem_len > 0) {
                *remainder = mx_strndup(buffer + rem_start, rem_len);
                if (!*remainder) return -1;
            }
            if (append(lineptr, buffer, i, line_len) == -1) return -1;
            return 1;
        }
    }
    return 0;
}

static int free_return(int res, char *buffer) {
    free(buffer);
    return res;
}

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    static char *rem = NULL;
    char *buffer = malloc(buf_size);
    if (!buffer) return -1;
    size_t len = 0;
    ssize_t bytes_read = 0;
    if (handle_rem(lineptr, &rem, &len) == -1)
        return free_return(-1, buffer);
    while ((bytes_read = read(fd, buffer, buf_size)) > 0) {
        int result = find_del(lineptr, buffer, bytes_read, delim, &rem, &len);
        if (result == 1) return free_return((int)len, buffer);
        else if (result == -1)  return free_return(-1, buffer);
        if (append(lineptr, buffer, bytes_read, &len) == -1)
            return free_return(-1, buffer);
    }
    free(buffer);
    return (bytes_read == -1) ? -1 : (int)len;
}

