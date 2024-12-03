#include "../inc/server.h"
#include "../inc/database_managment.h"

int main(int argc, const char * argv[]) {
    if (mx_init_server(argc, argv) == -1) {
      mx_printerr("Usage: ./uchat_server <port>\n");
    }

    if (mx_open_connection() < 0) return -1;
    else logger_info("connection opened\n");

    return 0;

    mx_accept_connections();
}
