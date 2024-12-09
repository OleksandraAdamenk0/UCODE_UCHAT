#include "server.h"
#include "database_managment.h"

int delete_message(sqlite3 *db, t_del_message *msg) {
    sqlite3_stmt *stmt;
    char *sql = "DELETE FROM message WHERE message_id = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    // Bind message_id
    if (sqlite3_bind_text(stmt, 1, msg->message_id, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return -2;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
       char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to delete message: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        sqlite3_finalize(stmt);
        return -3;
    }

    sqlite3_finalize(stmt);
    return 0;
}