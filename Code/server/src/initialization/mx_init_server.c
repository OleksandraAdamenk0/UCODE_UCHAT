//
// Created by aleksa on 11/2/24.
//
#include "server.h"
#include "initialization.h"

int port;
char *ip;

int mx_init_server(int argc, const char *argv[]) {
    // port
    t_arguments *arguments = mx_parse_args(argc, argv);
	if (!arguments) {
        mx_printerr("Usage: ./uchat_server <port>\n");
        return -1;
    }

    port = arguments->port;
    ip = mx_strdup(arguments->ip);
    free(arguments);

    // daemon
	if (mx_create_daemon() < 0) {
        mx_printerr("Failed during daemon creation\n");
        return -2;
    }

	// logger initialization
    if (logger_init(LOGGER_CONFIG) < 0) {
        mx_printerr("Failed during logger initialization\n");
        return -3;
    } else logger_info("Logger initialized\n");

    // database
    if (mx_db_init() < 0) {
        logger_fatal("Failed during database initialization");
        return -4;
    } else logger_info("Database initialized\n");
    return 0;
}
