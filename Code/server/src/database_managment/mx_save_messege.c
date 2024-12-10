#include "server.h"
#include "database_managment.h"

int save_message(sqlite3 *db, t_add_message *new_message) {
    char *sql = "INSERT INTO message (message_id, chat_id, timestamp, send_to_id, send_from_id, message, binary) VALUES (?, ?, ?, ?, ?, ?, ?)";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    // Bind values
    if (sqlite3_bind_text(stmt, 1, new_message->message_id, -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, new_message->chat_id, -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_int64(stmt, 3, new_message->timestamp) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 4, new_message->send_to_id, -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 5, new_message->send_from_id, -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 6, new_message->message, -1, SQLITE_STATIC) != SQLITE_OK) {
        
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to bind data: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        sqlite3_finalize(stmt);
        return -2;
    }

    // Handle binary data (photo)
    if (new_message->binary != NULL) {
        if (sqlite3_bind_blob(stmt, 7, new_message->binary, mx_strlen(new_message->binary), SQLITE_STATIC) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to bind data: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        sqlite3_finalize(stmt);
        return -2;
        }
    } else {
        if (sqlite3_bind_null(stmt, 7) != SQLITE_OK) {
            char err_msg[256];
            snprintf(err_msg, sizeof(err_msg), "Failed to bind data: %s\n", sqlite3_errmsg(db));
            logger_error(err_msg);
            sqlite3_finalize(stmt);
            return -2;
        }
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
       char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to bind data: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        sqlite3_finalize(stmt);
        return -2;
    }

    sqlite3_finalize(stmt);
    return 0;
}