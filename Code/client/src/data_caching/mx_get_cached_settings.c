#include "data_caching.h"

t_get_settings mx_get_cached_settings(sqlite3 *db) {
    sqlite3_stmt *stmt;
    char *sql = "SELECT * FROM settings";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        return NULL;
    }

    t_get_settings settings;
    settings.email = (char*)sqlite3_column_text(stmt, 0);
    settings.phone = (char*)sqlite3_column_text(stmt, 1);
    settings.photo = (char*)sqlite3_column_blob(stmt, 2);
    settings.theme = (char*)sqlite3_column_text(stmt, 3);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Execution failed: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
    }

    sqlite3_finalize(stmt);

    return settings;
}
