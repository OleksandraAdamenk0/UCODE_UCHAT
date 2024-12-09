#include "server.h"
#include "database_managment.h"

int is_data_in_table(sqlite3 *db, const char *table_name, const char *column_name, const char *value) {
    char sql[256];
    snprintf(sql, sizeof(sql), 
            "SELECT COUNT(*) FROM %s WHERE %s = ?;", 
            table_name, column_name);

    sqlite3_stmt *stmt;
    int count = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    if (sqlite3_bind_text(stmt, 1, value, -1, SQLITE_STATIC) != SQLITE_OK) {
        fprintf(stderr, "Failed to bind value: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    } else {
        fprintf(stderr, "Failed to execute query: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);

    if (count > 1) {
        fprintf(stderr, "Duplicate data found in table '%s' for column '%s'.\n", table_name, column_name);
        return -2; // Indicating duplicate data
    } else if (count == 1) {
        return 1; // Data exists and is unique
    } else {
        return 0; // Data does not exist
    }
}