//
// Created by oleksandra on 09/12/24.
//

#include "data_caching.h"
#include "data_exchange.h"
#include "responses.h"
#include "logger.h"
#include "libmx.h"
#include "client.h"
#include "utils.h"

#include <stdlib.h>

int mx_update_chats() {
    t_response *chats_response;
    if (mx_get_chats(id, &chats_response) < 0) {
        logger_warn("Failed to update db");
        return -1;
    }
    t_chats *chats_data = chats_response->data;
    if (!chats_data) {
        logger_warn("Failed to update db: no chats data in response");
        return -1;
    }

    const char *sql = "INSERT INTO chats (chat_id, chat_name, last_message) VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        char *msg = mx_sprintf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        logger_error(msg);
        free(msg);
        return -1;
    }

    for (int i = 0; i < chats_data->count; ++i) {
        // get last msg
        char *last_message = mx_get_last_message(chats_data->chats[i].id);
        if (!last_message) {
            char *msg = mx_sprintf("Failed to fetch last message for chat_id: %d\n", chats_data->chats[i].id);
            logger_warn(msg);
            free(msg);
            last_message = mx_strdup("");
        }

        // Bind chat_id
        if (sqlite3_bind_int(stmt, 1, chats_data->chats[i].id) != SQLITE_OK) {
            char *msg = mx_sprintf("Failed to bind chat_id: %s\n", sqlite3_errmsg(db));
            logger_error(msg);
            free(msg);
            sqlite3_finalize(stmt);
            free(last_message);
            return -1;
        }

        // Bind chat_name
        if (sqlite3_bind_text(stmt, 2, chats_data->chats[i].name, -1, SQLITE_STATIC) != SQLITE_OK) {
            char *msg = mx_sprintf("Failed to bind chat_name: %s\n", sqlite3_errmsg(db));
            logger_error(msg);
            free(msg);
            sqlite3_finalize(stmt);
            free(last_message);
            return -1;
        }

        // Bind last_message
        if (sqlite3_bind_text(stmt, 3, last_message, -1, SQLITE_TRANSIENT) != SQLITE_OK) {
            char *msg = mx_sprintf("Failed to bind last_message: %s\n", sqlite3_errmsg(db));
            logger_error(msg);
            free(msg);
            sqlite3_finalize(stmt);
            free(last_message);
            return -1;
        }

        // Bind photo (((((((
        // Execute the statement
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            char *msg = mx_sprintf("Failed to insert chat: %s\n", sqlite3_errmsg(db));
            logger_error(msg);
            free(msg);
            sqlite3_finalize(stmt);
            free(last_message);
            return -1;
        }

        sqlite3_reset(stmt);
        free(last_message);
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    logger_info("Successfully inserted all chats\n");
    return 0;
}