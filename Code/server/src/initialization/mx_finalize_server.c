//
// Created by oleksandra on 28/11/24.
//

#include "server.h"
#include "connection.h"
#include "logger.h"

#include <unistd.h>

void mx_finalize_server() {
    if (svr_fd > 0) close(svr_fd);
    svr_fd = -1;
    logger_close();
//    mx_db_finalize();
}
