//
// Created by aleksa on 11/2/24.
//

#include "server.h"
#include "initialization.h"
#include "logger.h"

int port;
char *ip;

int mx_init_server(int argc, const char *argv[]) {
    if (mx_parse_args(argc, argv, &port) < 0) {
        mx_printerr("Usage: ./uchat_server <port>\n");
        return -1;
    }
    ip = "127.0.0.1";

    // daemon
    if (mx_init_daemon() < 0) {
        // mx_printerr("Failed during daemon creation\n");
        return -2;
    }

    // logger initialization
    if (logger_init(LOGGER_CONFIG) < 0) {
        // mx_printerr("Failed during logger initialization\n");
        return -3;
    }
    logger_info("Logger initialized\n");

    // database
    if (mx_init_db() < 0) {
        logger_fatal("Failed during database initialization");
        return -4;
    }
    logger_info("Database initialized\n");
    return 0;
}
