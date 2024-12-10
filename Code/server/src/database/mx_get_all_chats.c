#include "server.h"
#include "logger.h"
#include "utils.h"
#include "database.h"
#include "responses.h"

#include <stdlib.h>

t_list *mx_get_all_chats(int id) {
    sqlite3_stmt *stmt;
    t_list *chat_list = NULL;
    char *sql = "SELECT DISTINCT c.id, c.chat_name, c.photo FROM chats c "
                "JOIN chats_users cu ON cu.chat_id = c.id "
                "WHERE cu.user_id = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        char *err_msg = mx_sprintf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        free(err_msg);
        return NULL;
    }

    // bind user id
    if (sqlite3_bind_int(stmt, 1, id) != SQLITE_OK) {
        char *err_msg = mx_sprintf("Failed to bind user_id: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        free(err_msg);
        sqlite3_finalize(stmt);
        return NULL;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        t_chat *chat = malloc(sizeof(t_chat));
        chat->id = sqlite3_column_int(stmt, 0);
        chat->name = (char*)sqlite3_column_text(stmt, 1);
//        chat.photo = (char*)sqlite3_column_blob(stmt, 3);
        mx_push_front(&chat_list, chat);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        char *err_msg = mx_sprintf("Execution failed: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        free(err_msg);
        return NULL;
    }

    sqlite3_finalize(stmt);
    return chat_list;
}
