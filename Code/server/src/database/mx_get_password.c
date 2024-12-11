//
// Created by oleksandra on 09/12/24.
//

#include "database.h"
#include "logger.h"
#include "libmx.h"

#include <stdlib.h>

char *mx_get_password(int id) {
    char *query = "SELECT password FROM users WHERE id = ?;";

    sqlite3_stmt *stmt;
    char *password = NULL; // Default to -1 if user not found
    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) return NULL;
    logger_debug("stmt created");
    // Bind the username to the query
    if (sqlite3_bind_text(stmt, 1, mx_itoa(id), -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return NULL;
    }
    logger_debug("id bound");
    // Execute the query and retrieve the password
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *data = sqlite3_column_text(stmt, 0);
        logger_debug("query executed");
        logger_debug(data);
        password = mx_strdup((char *)(data));
    }
    // Finalize the statement to avoid memory leaks
    sqlite3_finalize(stmt);
    return password;
}
