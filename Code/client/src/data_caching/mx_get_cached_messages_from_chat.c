#include "data_caching.h"

t_list *mx_get_cached_messages_from_chat(sqlite3 *db, int chat_id) {
    sqlite3_stmt *stmt;
    t_list *messages_list = NULL;
    char *sql = "SELECT * FROM messages WHERE chat_id = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        return NULL;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        t_get_msgs message;
        message.id = sqlite3_column_int(stmt, 0);
        message.receiver = sqlite3_column_int(stmt, 1);
        message.sender = (char*)sqlite3_column_text(stmt, 2);
        message.timestamp = (char*)sqlite3_column_text(stmt, 3);
        message.binary = (char*)sqlite3_column_blob(stmt, 4);
        message.message = (char*)sqlite3_column_text(stmt, 5);
        mx_push_front(&messages_list, &message);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Execution failed: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
    }

    sqlite3_finalize(stmt);

    return messages_list;
}
