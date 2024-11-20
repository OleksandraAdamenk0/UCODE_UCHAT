#include "../inc/server.h"

int main(int argc, const char * argv[]) {
    if (mx_init_server(argc, argv) == -1) {
      mx_printerr("Usage: ./uchat_server <port>\n");
    }

    if (mx_open_connection() < 0) return -1;
    else logger_info("connection opened\n");

    mx_accept_connections();
}
