//
// created by herman on 22/11/24.
//

#include "connection.h"
#include "libmx.h"
#include "logger.h"

#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

static int get_amount(const char *data) {
    int data_len = mx_strlen(data);
    return (data_len + BUFFER_SIZE - 2) / (BUFFER_SIZE - 1);
}

static int send_amount(int fd, int amount) {
    char *num_str = mx_itoa(amount);
    char buffer[BUFFER_SIZE];
    mx_memset(buffer, '\0', BUFFER_SIZE);
    mx_strncpy(buffer, num_str, mx_strlen(num_str));
    logger_debug(buffer);
    if (send(fd, buffer, BUFFER_SIZE, 0) < 0) return -1;
    return 0;
}

static int send_content( int fd, int amount, char *data) {
    for (int i = 0; i < amount; ++i) {
        int data_len = mx_strlen(data);
        int len = data_len > (BUFFER_SIZE - 1) ? (BUFFER_SIZE - 1) : data_len;
        char buffer[BUFFER_SIZE];
        mx_memset(buffer, '\0', BUFFER_SIZE);

        mx_strncpy(buffer, data, len);
        logger_debug(buffer);
        data += len;

        if (send(fd, buffer, 1024, 0) < 0) return -1;
    }
    return 0;
}

int mx_send_data(int fd, char *data) {
    logger_debug("mx_send_data");
    if (!data) return -1;  // no data to send
    int amount = get_amount(data);
    if (send_amount(fd, amount) < 0) return -2;
    logger_debug("amount sent");
    if (send_content(fd, amount, data) < 0) return -3;
    logger_debug("content sent");
    return 0;
}
