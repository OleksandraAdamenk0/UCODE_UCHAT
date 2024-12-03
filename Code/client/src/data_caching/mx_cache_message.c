#include "data_caching.h"
#include "client.h"

int mx_cache_message(sqlite3 *db, t_get_msgs msg) {
    sqlite3_stmt *stmt;
    char *sql = "INSERT OR IGNORE INTO messages VALUES (?, ?, ?, ?, ?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        return -1;
    }

    sqlite3_bind_int(stmt, 1, msg.id);
    sqlite3_bind_int(stmt, 2, msg.receiver);
    sqlite3_bind_text(stmt, 3, msg.sender, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, msg.timestamp, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, msg.message, -1, SQLITE_STATIC);

    if (msg.binary != NULL) {
        int binary_size = sizeof(msg.binary);
        sqlite3_bind_blob(stmt, 5, msg.binary, binary_size, SQLITE_STATIC);
    } else {
        sqlite3_bind_null(stmt, 5);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        char error[128];
        snprintf(error, sizeof(error), "Message caching failed: %s\n", sqlite3_errmsg(db));
        logger_error(error);
        sqlite3_finalize(stmt);
        return -1;
    } else {
        logger_info("Message cached successfully.\n");
    }

    sqlite3_finalize(stmt);

    const char *cleanup_sql =
        "DELETE FROM messages WHERE id NOT IN ("
        "SELECT id FROM messages ORDER BY timestamp DESC LIMIT 50"
        ")";

    if (sqlite3_prepare_v2(db, cleanup_sql, -1, &stmt, NULL) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to prepare cleanup statement: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        return -1;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        char error[128];
        snprintf(error, sizeof(error), "Cleanup execution failed: %s\n", sqlite3_errmsg(db));
        logger_error(error);
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    return 0;
}
