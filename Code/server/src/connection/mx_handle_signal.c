//
// Created by oleksandra on 17/11/24.
//

#include "connection.h"
#include "logger.h"

void mx_handle_signal(int sig) {
    if (sig == SIGTERM || sig == SIGINT) server_running = 0;
    logger_debug("kill signal received\n");
}