#include "server.h"
#include "database_managment.h"

int mx_delete_chat(sqlite3 *db, int chat_id) {
    sqlite3_stmt *stmt;
    char *sql = "DELETE FROM chats WHERE chat_id = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        return -1;
    }

    sqlite3_bind_int(stmt, 1, chat_id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to delete chat: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        sqlite3_finalize(stmt);
        return -2;
    }

    sqlite3_finalize(stmt);
    return 0;
}