//
// Created by oleksandra on 04/12/24.
//

#include "data_caching.h"
#include "logger.h"

sqlite3 *db;

static int create_dir() {
    struct stat st = {0};
    if (stat(DB_DIR, &st) == -1)
        if (mkdir(DB_DIR, 0777) != 0 && errno != EEXIST) return -1;
    return 0;
}

int mx_init_db() {
    if (create_dir() < 0) {
        logger_warn("Error opening/creating database\n");
        logger_debug("Failed to create database directory\n");
        return -1;
    }
    if (sqlite3_open(DB_NAME, &db) != SQLITE_OK) {
        logger_warn("Error opening/creating database\n");
        return -1;
    }
    logger_info("Database was opened/created\n");
    return 0;
}