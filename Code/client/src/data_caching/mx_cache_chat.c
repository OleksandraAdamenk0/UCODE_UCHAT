#include "data_caching.h"
#include "client.h"

int mx_cache_chat(sqlite3 *db, t_get_chats chat) {
    sqlite3_stmt *stmt;
    char *sql = "INSERT INTO chats VALUES (?, ?, ?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to prepare statement: %s\n", sqlite3_errmsg(db))
        logger_error(err_msg);
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_int(stmt, 1, chat.chat_id);
    sqlite3_bind_text(stmt, 2, chat.chat_name, -1, NULL);
    sqlite3_bind_text(stmt, 3, chat.last_message, -1, NULL);

    if (chat.photo != NULL) {
        size_t photo_size = sizeof(chat.photo);
        unsigned char *photo_data = base64_decode(chat.photo, photo_size, &photo_size);

        if (photo_data != NULL) {
            sqlite3_bind_blob(stmt, 4, photo_data, photo_size, SQLITE_STATIC);
            free(photo_data);
        } else {
            logger_error("Failed to decode photo data.\n");
            sqlite3_finalize(stmt);
            return -1;
        }
    } else {
        // Bind NULL if no photo is provided
        sqlite3_bind_null(stmt, 4);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        char error[128];
        snprintf(error, sizeof(error), "Execution failed: %s\n", sqlite3_errmsg(db));
        logger_error(error);
        sqlite3_finalize(stmt);
        return -1;
    } else {
        logger_info("Chat saved successfully.\n");
    }

    sqlite3_finalize(stmt);
    return 0;
}
