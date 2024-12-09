#include "server.h"
#include "database_managment.h"

int create_new_chat(sqlite3 *db, t_chat_req *chat_data) {
    sqlite3_stmt *stmt;
    char *sql = "INSERT INTO chat (chat_id, chat_name) VALUES (?, ?)";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    // Bind chat_id
    if ((sqlite3_bind_text(stmt, 1, chat_data->chat_id, -1, SQLITE_STATIC) != SQLITE_OK) ||
    (sqlite3_bind_text(stmt, 2, chat_data->chat_name, -1, SQLITE_STATIC) != SQLITE_OK)) {
        sqlite3_finalize(stmt);
        return -2;
    }
    

    if (is_data_in_table(db, "chat", "chat_id", chat_data->chat_id) || mx_strcmp(chat_data->chat_id, "") == 0) {
        fprintf(stderr, "Invalid or missing chat_id.\n");
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
