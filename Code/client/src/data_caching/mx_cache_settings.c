#include <sqlite3.h>

#include "data_caching.h"
#include "client.h"

int mx_cache_settings(sqlite3 *db, t_get_settings settings) {
    sqlite3_stmt *stmt;
    char *sql = "INSERT OR IGNORE INTO settings VALUES (?, ?, ?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, settings.email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, settings.phone, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, settings.theme, -1, SQLITE_STATIC);

    if (settings.photo != NULL) {
        int photo_size = sizeof(settings.photo);
        sqlite3_bind_blob(stmt, 3, settings.photo, photo_size, SQLITE_STATIC);
    } else {
        sqlite3_bind_null(stmt, 3);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        char error[128];
        snprintf(error, sizeof(error), "Execution failed: %s\n", sqlite3_errmsg(db));
        logger_error(error);
        sqlite3_finalize(stmt);
        return -1;
    } else {
        logger_info("Settings saved successfully.\n");
    }

    sqlite3_finalize(stmt);
    return 0;
}
