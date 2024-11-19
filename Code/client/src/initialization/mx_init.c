//
// Created by oleksandra on 17/11/24.
//

#include "client.h"
#include "initialization.h"

int port;
char *ip;

int mx_init(int argc, const char * argv[]) {

    // arguments
    arguments *arguments = mx_parse_args(argc, argv);
    if (!arguments) return -1;

    port = arguments->port;
    ip = arguments->ip;
    free(arguments);

    // logger
    if (logger_init(LOGGER_CONFIG) < 0) return -1;
    logger_info("logger initialized\n");

    // gtk init
    gtk_init(&argc, &argv);

    return 0;
}
