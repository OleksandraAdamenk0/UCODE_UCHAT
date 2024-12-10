//
// Created by oleksandra on 22/11/24.
//

#include "database.h"
#include "logger.h"

#include <stdlib.h>

sqlite3 *db;

static int execute_sql_script(const char *script) {
    if (!db) return -1;
    char *errmsg = NULL;
    int rc = sqlite3_exec(db, script, 0, 0, &errmsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errmsg);
        return rc;
    }
    return SQLITE_OK;
}

static int file_exists(const char *filename) {
    struct stat buffer;
    return stat(filename, &buffer) == 0;
}

int mx_init_db() {
    int is_new_db = !file_exists(DB_NAME);

    if (sqlite3_open_v2(DB_NAME, &db,
                        SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE |
                        SQLITE_OPEN_FULLMUTEX, NULL) != SQLITE_OK) {
        logger_fatal("Error opening/creating database\n");
        logger_debug("Failed to open or create db file\n");
        return -1;
    } logger_debug("Database file opened\n");


    sqlite3_busy_timeout(db, 1000);
    sqlite3_config(SQLITE_CONFIG_MULTITHREAD);

    if (is_new_db) {
        logger_debug("New database file detected. Executing initialization script.\n");

        char *cmd = mx_file_to_str(INIT_SCRIPT);
        if (!cmd) {
            logger_debug("Error occurred while trying to read script\n");
            sqlite3_close(db);
            return -2;
        }
        logger_debug("SQL script read\n");

        if (execute_sql_script(cmd) != SQLITE_OK) {
            free(cmd);
            logger_debug("Error occurred while trying to execute script\n");
            sqlite3_close(db);
            return -3;
        }
        logger_debug("SQL script executed\n");
        free(cmd);
    } else {
        logger_debug("Database file already exists. Skipping initialization script.\n");
    }

    return 0;
}
