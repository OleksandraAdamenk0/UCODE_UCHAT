//
// created by herman on 22/11/24.
//

#include "connection.h"
#include "libmx.h"
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
    if (send(fd, buffer, BUFFER_SIZE, 0) < 0) return -1;
    return 0;
}

static int send_content( int fd, int amount, char *data) {
    for (int i = 0; i < amount; ++i) {
        int len = (mx_strlen(data) > (BUFFER_SIZE - 1)) ? (BUFFER_SIZE - 1) : mx_strlen(data);
        char buffer[BUFFER_SIZE];
        mx_memset(buffer, '\0', BUFFER_SIZE);

        mx_strncpy(buffer, data, len);
        data += len;

        if (send(fd, buffer, 1024, 0) < 0) return -1;
    }
    return 0;
}

int mx_send_data(int fd, char *data) {
    if (!data) return -1;  // no data to send
    int amount = get_amount(data);
    if (send_amount(fd, amount) < 0) return -2;
    if (send_content(fd, amount, data) < 0) return -3;
    return 0;
}

