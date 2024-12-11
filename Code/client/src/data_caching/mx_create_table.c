#include "data_caching.h"
#include "logger.h"
#include "libmx.h"
#include "utils.h"

#include <stdlib.h>

static int execute_sql(const char *cmd) {
    if (!db) return -1;
    char *errmsg = NULL;
    int rc = sqlite3_exec(db, cmd, 0, 0, &errmsg);
    if (rc != SQLITE_OK) {
        char *msg = mx_sprintf("Failed to execute sql cmd. Errmsg: %s", errmsg);
        logger_error(msg);
        free(msg);
        sqlite3_free(errmsg);
        return rc;
    }
    return SQLITE_OK;
}

int mx_create_tables() {
    if (sqlite3_open_v2(DB_NAME, &db,
                        SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE |
                        SQLITE_OPEN_FULLMUTEX, NULL) != SQLITE_OK) {
        logger_fatal("Error opening/creating database");
        logger_debug("Failed to open or create db file");
        return -1;
    } logger_debug("Database file opened");

//    if we manage to do the second thread to receive the data
//    sqlite3_busy_timeout(db, 1000);
//    sqlite3_config(SQLITE_CONFIG_MULTITHREAD);

    char *cmd = mx_file_to_str(INIT_SCRIPT);
    if (!cmd) {
        logger_debug("Error occurred while trying to read script\n");
        sqlite3_close(db);
        return -2;
    }
    logger_debug("SQL script read\n");

    if (execute_sql(cmd) != SQLITE_OK) {
        free(cmd);
        logger_debug("Error occurred while trying to execute script\n");
        sqlite3_close(db);
        return -3;
    }
    logger_debug("SQL script executed\n");
    free(cmd);

    return 0;
}
