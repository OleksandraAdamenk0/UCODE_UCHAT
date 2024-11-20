#include "client.h"

int main(int argc, const char * argv[]) {
    if (mx_init(argc, argv) < 0) {
        mx_printerr("Usage: ./uchat <ip_address> <port>\n");
        return -1;
    }
    int fd = mx_open_connection();
    if (fd == -1) return -1;
    if (fd == -2) {
        logger_error("connection failed\n");
        logger_warn("the app is running in offline mode\n");

        // transition to offline mode logic here

    } else logger_info("connection opened\n");

    // ...
    debug_send(fd, "test string\n");

    mx_close_connection(fd);
    logger_info("connection closed\n");
    return 0;
}
