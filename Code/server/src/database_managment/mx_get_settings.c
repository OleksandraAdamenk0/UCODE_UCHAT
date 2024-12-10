#include "server.h"
#include "database_managment.h"

int return_settings(sqlite3 *db, t_get_settings *user, t_add_settings *settings) {
    sqlite3_stmt *stmt;
    char *sql = "SELECT * FROM settings WHERE user_id = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    if (sqlite3_bind_text(stmt, 1, &user->user_id, 1, SQLITE_STATIC) != SQLITE_OK) {
        fprintf(stderr, "Failed to bind user_id: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -2;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Copy settings data
        settings->user_id = *((const char *)sqlite3_column_text(stmt, 0));
        settings->theme = *((const char *)sqlite3_column_text(stmt, 1));
        settings->email = *((const char *)sqlite3_column_text(stmt, 2));
        settings->phone = *((const char *)sqlite3_column_text(stmt, 3));

        // Photo handling
        const void *photo_blob = sqlite3_column_blob(stmt, 4);
        int photo_size = sqlite3_column_bytes(stmt, 4);

        if (photo_blob && photo_size > 0) {
            settings->photo = *((const char *)photo_blob);
        } else {
            settings->photo = '\0'; // Default to null character if no photo
        }
    } else {
        fprintf(stderr, "No matching records found.\n");
        sqlite3_finalize(stmt);
        return -3;
    }

    sqlite3_finalize(stmt);
    return 0;
}

