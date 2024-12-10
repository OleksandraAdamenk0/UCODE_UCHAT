//
// Created by oleksandra on 22/11/24.
//
#include "server.h"
#include "database_managment.h"

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

int mx_db_init() {
    if (sqlite3_open_v2(DB_NAME, &db,
                        SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE |
                        SQLITE_OPEN_FULLMUTEX, NULL) != SQLITE_OK) {
        logger_fatal("Error opening/creating database\n");
        logger_debug("Failed to open or create db file\n");
        return -1;
    } logger_debug("Database file opened\n");


    sqlite3_busy_timeout(db, 1000);
    sqlite3_config(SQLITE_CONFIG_MULTITHREAD);

    char *cmd = mx_file_to_str(INIT_SCRIPT);
    if (!cmd) {
        logger_debug("Error occurred while trying to read script\n");
        return -2;
    } logger_debug("SQL script read\n");

    if (execute_sql_script(cmd) != SQLITE_OK) {
        free(cmd);
        logger_debug("Error occurred while trying to execute script\n");
        return -3;
    } else logger_debug("SQL script executed\n");

    free(cmd);
    return 0;
}