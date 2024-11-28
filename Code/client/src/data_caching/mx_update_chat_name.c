#include "../../inc/data_caching.h"

int mx_update_chat_name(sqlite3 *db, char *new_chat_name, int chat_id) {
    sqlite3_stmt *stmt;
    char *sql = "UPDATE chats SET chat_name = ? WHERE chat_id = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, new_chat_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, chat_id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Execution failed: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    return 0;
}
