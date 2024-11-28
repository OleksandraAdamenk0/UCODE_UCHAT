//
// Created by oleksandra on 28/11/24.
//

#include "server.h"

void mx_finalize_server() {
    logger_close();
    mx_db_finalize();
}
