#include "client.h"

int main(int argc, char *argv[]) {

    if (mx_init(argc, argv) < 0) {
        mx_printerr("Usage: ./uchat <ip_address> <port>\n");
        return -1;
    }
    int fd = mx_open_connection();
    if (fd == -1) return -1;
    if (fd == -2) {
        logger_error("connection failed\n");
        logger_warn("the app is running in offline mode\n");
        // check if local db exists and not empty,
        // to know that data for the offline mode can be loaded
        // if so - load data and pop up window with warning about offline mode
        // otherwise load static page showing error
    } else {
        logger_info("connection opened\n");
        // ...
        debug_send(fd, "test string\n");
    }

    if (mx_gui_network_error() < 0) {
        mx_close_connection(fd);
        logger_info("connection closed\n");
        return -1;
    }

    mx_close_connection(fd);
    logger_info("connection closed\n");
    return 0;
}
