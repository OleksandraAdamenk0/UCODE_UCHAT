//
// Created by oleksandra on 22/11/24.
//

#include "server.h"
#include "database_managment.h"

void mx_db_finalize() {
    if (db) sqlite3_close(db);
    logger_info("database closed\n");
}
