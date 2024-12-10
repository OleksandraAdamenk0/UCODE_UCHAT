//
// Created by oleksandra on 22/11/24.
//

#include "server.h"
#include "logger.h"
#include "database.h"

void mx_db_finalize() {
    if (db) sqlite3_close(db);
    logger_info("database closed\n");
}
