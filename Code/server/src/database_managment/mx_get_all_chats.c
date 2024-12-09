#include "server.h"
#include "database_managment.h"

t_list *mx_get_all_chats(sqlite3 *db) {
    sqlite3_stmt *stmt;
    t_list *chat_list = NULL;
    char *sql = "SELECT * FROM chats";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        return -1;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        t_chat_req chat;
        chat.chat_id = sqlite3_column_int(stmt, 0);
        chat.chat_name = (char*)sqlite3_column_text(stmt, 1);
        chat.photo = (char*)sqlite3_column_blob(stmt, 3);
        mx_push_front(&chat_list, &chat);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Execution failed: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        return -1;
    }

    sqlite3_finalize(stmt);

    return chat_list;
}