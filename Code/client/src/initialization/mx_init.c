//
// Created by oleksandra on 03/12/24.
//

#include "client.h"
#include "initialization.h"
#include "data_caching.h"
#include "connection.h"
#include "logger.h"
#include "libmx.h"
#include "utils.h"

int port;
char *ip;
long long int id;

int mx_init(int argc, const char *argv[]) {
    // check arguments
    port = -1;
    ip = NULL;
    id = 0;

    if (mx_parse_args(argc, argv, &port, &ip) < 0) {
        mx_printerr("Usage: ./uchat <ip_address> <port>\n");
        return -1;
    }

    // initialize logger
    if (logger_init(LOGGER_CONFIG) < 0) return -1;
    logger_info("mx_init: Logger initialized");

    // initialize gtk
    if (mx_init_gtk() < 0) {
        logger_error("mx_init: GTK initialization failed");
        return -1;
    }

    // initialize db
    if (mx_init_db() < 0) {
        logger_error("mx_init: DB initialization failed");
        return -1;
    }
    return 0;
}
