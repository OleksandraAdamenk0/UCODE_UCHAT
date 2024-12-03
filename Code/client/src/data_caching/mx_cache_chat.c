#include "data_caching.h"
#include "client.h"

int mx_cache_chat(sqlite3 *db, t_get_chats chat) {
    sqlite3_stmt *stmt;
    char *sql = "INSERT OR IGNORE INTO chats VALUES (?, ?, ?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        return -1;
    }

    sqlite3_bind_int(stmt, 1, chat.chat_id);
    sqlite3_bind_text(stmt, 2, chat.chat_name, -1, NULL);
    sqlite3_bind_text(stmt, 3, chat.last_message, -1, NULL);

    if (chat.photo != NULL) {
        int photo_size = sizeof(chat.photo);
        sqlite3_bind_blob(stmt, 4, chat.photo, photo_size, SQLITE_STATIC);
    } else {
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
