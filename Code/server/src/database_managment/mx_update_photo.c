#include "server.h"
#include "database_managment.h"

int mx_update_photo(sqlite3 *db, const char *table_name, const char *condition_column,
                    const char *new_photo, int new_photo_size, 
                    const char *condition_value, int condition_size) {
    sqlite3_stmt *stmt;
    char sql[256];
    
    // Construct the SQL query
    snprintf(sql, sizeof(sql), "UPDATE %s SET photo = ? WHERE %s = ?", 
             table_name, condition_column);
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        return -1;
    }

    // Bind new photo
    if (new_photo != NULL) {
        sqlite3_bind_blob(stmt, 1, new_photo, new_photo_size, SQLITE_STATIC);
    } else {
        sqlite3_bind_null(stmt, 1);
    }

    // Bind condition value
    if (condition_value != NULL) {
        sqlite3_bind_blob(stmt, 2, condition_value, condition_size, SQLITE_STATIC);
    } else {
        sqlite3_bind_null(stmt, 2);
    }

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Updating photo in table %s failed: %s\n", 
                 table_name, sqlite3_errmsg(db));
        logger_error(err_msg);
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    return 0;
}