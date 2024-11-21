#include "../../inc/data_caching.h"

bool file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true; // File exists
    }
    return false; // File does not exist
}

// Function to check if any of the specified tables have data
bool has_data_in_tables(sqlite3 *db, const char *tables[], int num_tables) {
    for (int i = 0; i < num_tables; i++) {
        const char *sql = "SELECT * FROM ";
        char query[256]; // Buffer for the SQL query
        snprintf(query, sizeof(query), "%s%s;", sql, tables[i]);

        sqlite3_stmt *stmt;
        int rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            // Error in SQL statement
            return false;
        }

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);
            if (count > 0) {
                return true; // true, at least one table has data
            }
        } else {
            // Error in executing the statement
            sqlite3_finalize(stmt);
            return false;
        }
        sqlite3_finalize(stmt);
    }
    return false;
}

// Function to check if the SQLite database is valid (exists and not empty)
bool mx_is_database_valid(const char *db_path) {
    sqlite3 *db;
    int rc;

    // Check if the database file exists
    if (!file_exists(db_path)) {
        return false;
    }

    rc = sqlite3_open(db_path, &db);
    if (rc != SQLITE_OK) {
        // Error opening the database
        sqlite3_close(db);
        return false;
    }

    const char *tables[] = {"chats", "contacts", "messages", "settings"};
    int num_tables = 4;

    bool has_data = has_data_in_tables(db, tables, num_tables);

    sqlite3_close(db);
    return has_data;
}

