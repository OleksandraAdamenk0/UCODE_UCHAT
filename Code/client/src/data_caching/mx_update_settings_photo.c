#include "../../inc/data_caching.h"

int mx_update_settings_photo(sqlite3 *db, char *new_photo, int new_photo_size, char *old_photo, int old_photo_size) {
    sqlite3_stmt *stmt;
    char *sql = "UPDATE settings SET photo = ? WHERE photo = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        return -1;
    }

    if (new_photo != NULL) {
        sqlite3_bind_blob(stmt, 1, new_photo, new_photo_size, SQLITE_STATIC);
    } else {
        sqlite3_bind_null(stmt, 1);
    }

    if (old_photo != NULL) {
        sqlite3_bind_blob(stmt, 2, old_photo, old_photo_size, SQLITE_STATIC);
    } else {
        sqlite3_bind_null(stmt, 2);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Updating settings photo failed: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    return 0;
}
