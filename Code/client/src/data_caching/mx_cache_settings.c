#include "../../inc/data_caching.h"
#include "../../inc/client.h"

int mx_cache_chat(sqlite3 *db, t_get_settings settings) {
    sqlite3_stmt *stmt;
    char *sql = "INSERT INTO chats VALUES (?, ?, ?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, settings.email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, settings.phone, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, settings.theme, -1, SQLITE_STATIC);

    if (settings.photo != NULL) {
        int photo_size = sizeof(settings.photo);
        unsigned char *photo_data = base64_decode(settings.photo, photo_size, &photo_size);

        if (photo_data != NULL) {
            sqlite3_bind_blob(stmt, 3, photo_data, photo_size, SQLITE_STATIC);
            free(photo_data);
        } else {
            logger_error("Failed to decode photo data.\n");
            sqlite3_finalize(stmt);
            return -1;
        }
    } else {
        // Bind NULL if no photo is provided
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

    return 0;
}
