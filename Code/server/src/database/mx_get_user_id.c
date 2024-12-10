//
// Created by oleksandra on 26/11/24.
//

#include "database.h"
#include "logger.h"

#include <stdlib.h>

int mx_get_user_id(const char *value, t_users_field field) {
    char *query = NULL;
    if (field == USERNAME) query = "SELECT id FROM users WHERE username = ?;";
    if (field == EMAIL) query = "SELECT id FROM users WHERE email = ?;";
    if (field == PHONE) query = "SELECT id FROM users WHERE phone = ?;";
    if (!query) return -2;

    sqlite3_stmt *stmt;
    int id = -1; // Default to -1 if user not found
    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) return -2;
    logger_debug("stmt created");
    // Bind value to the query
    if (sqlite3_bind_text(stmt, 1, value, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return -2;
    }
    logger_debug("value bound");
    // Execute the query and retrieve the user ID
    if (sqlite3_step(stmt) == SQLITE_ROW) id = sqlite3_column_int(stmt, 0);
    logger_debug("query executed");
    // Finalize the statement to avoid memory leaks
    sqlite3_finalize(stmt);
    return id;
}
