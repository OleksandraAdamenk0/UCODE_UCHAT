//
// Created by aleksa on 11/2/24.
//
#include "server.h"
#include "initialization.h"

int port;
char *ip = "127.0.0.1";

int mx_init_server(int argc, const char * argv[]) {
    port = mx_parse_args(argc, argv);
	if (port < 1) return -1;

	if (mx_create_daemon() < 0) return -2;
	// logger initialization
	logger_init(LOGGER_CONFIG);
    logger_info("Logger initialized\n");
	return 0;
}
