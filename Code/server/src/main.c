#include "server.h"

int main(int argc, const char *argv[]) {
    if (mx_init_server(argc, argv) < 0) return -1;
    else logger_info("Server initialized\n");

    if (mx_open_connection() < 0) {
        mx_finalize_server();
        return -1;
    }

    if (mx_accept_connections() < 0) {
        mx_finalize_server();
        return -1;
    }

    mx_finalize_server();
    return 0;
}
