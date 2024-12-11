//
// Created by maksym_ch on 11.12.24.
//
#include "data_caching.h"

int mx_update_contacts() {
    t_response *contacts_response;
    if (mx_get_contacts(id, &contacts_response) < 0) {
        logger_warn("Failed to update db");
        return -1;
    }
    t_contacts *contacts_data = contacts_response->data;
    if (!contacts_data) {
        logger_warn("Failed to update db: no contacts data in response");
        return -1;
    }

    const char *sql = "INSERT INTO contacts (username) VALUES (?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        char *msg = mx_sprintf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        logger_error(msg);
        free(msg);
        return -1;
    }

    for (int i = 0; i < contacts_data->count; ++i) {
        // Bind chat_id
        if (sqlite3_bind_text(stmt, 1, contacts_data->contacts[i].username, -1, SQLITE_STATIC) != SQLITE_OK) {
            char *msg = mx_sprintf("Failed to bind username: %s\n", sqlite3_errmsg(db));
            logger_error(msg);
            free(msg);
            sqlite3_finalize(stmt);
            return -1;
        }

        // Execute the statement
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            char *msg = mx_sprintf("Failed to insert contact: %s\n", sqlite3_errmsg(db));
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

    logger_info("Successfully inserted all contacts\n");
    return 0;
}
