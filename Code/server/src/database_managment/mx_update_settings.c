#include "server.h"
#include "database_managment.h"

int mx_update_settings_theme(sqlite3 *db, char *new_theme, char *old_theme) {
    sqlite3_stmt *stmt;
    char *sql = "UPDATE settings SET theme = ? WHERE theme = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, new_theme, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, old_theme, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Updating settings theme failed: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    return 0;
}