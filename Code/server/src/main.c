#include "server.h"

int main(int argc, const char * argv[]) {
    if (mx_init_server(argc, argv) == -1) {
        mx_printerr("Usage: ./uchat_server <port>\n");
        return -1;
    } else logger_info("server initialized\n");

    if (mx_open_connection() < 0) return -1;
    else logger_info("connection channel opened\n");

    mx_accept_connections();
}
