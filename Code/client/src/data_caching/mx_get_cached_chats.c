#include "data_caching.h"

t_list *mx_get_cached_chats(sqlite3 *db) {
    sqlite3_stmt *stmt;
    t_list *chats_list = NULL;
    char *sql = "SELECT * FROM chats";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        return NULL;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        t_get_chats chats;
        chats.chat_id = sqlite3_column_int(stmt, 0);
        chats.chat_name = (char*)sqlite3_column_text(stmt, 1);
        chats.last_message = (char*)sqlite3_column_text(stmt, 2);
        chats.photo = (char*)sqlite3_column_blob(stmt, 3);
        mx_push_front(&chats_list, &chats);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Execution failed: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
    }

    sqlite3_finalize(stmt);

    return chats_list;
}
