#include "server.h"
#include "database_managment.h"

int add_user_to_chat(sqlite3 *db, t_add_user_chat *chat_user_data) {
    sqlite3_stmt *stmt;
    char *sql = "INSERT INTO chat_user (chat_id, user_id) VALUES (?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    if ((sqlite3_bind_text(stmt, 1, chat_user_data->chat_id, -1, SQLITE_STATIC) != SQLITE_OK) ||
    (sqlite3_bind_text(stmt, 2, chat_user_data->user_id, -1, SQLITE_STATIC) != SQLITE_OK)) {
    char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to bind: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        sqlite3_finalize(stmt);
        return -2;
    }

    if (is_data_in_table(db, "chat_user", "user_id", chat_user_data->user_id) == -2) {
        fprintf(stderr, "User already in chat.\n");
        sqlite3_finalize(stmt);
        return -2;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        const char *error_msg = sqlite3_errmsg(db);
        fprintf(stderr, "SQLite error: %s\n", error_msg);
        sqlite3_finalize(stmt);
        if (mx_strcmp(UNIQUE_USERNAME, error_msg) == 0) return -2;
        return -1;
    }

    sqlite3_finalize(stmt);
    return 0;
}