#include "client.h"
#include "data_caching.h"

static bool dir_exists(const char *dirname) {
    struct stat buffer;
    if (stat(dirname, &buffer) == 0) {
        if (S_ISDIR(buffer.st_mode)) return true;
        else return false;
    }
    return false;
}

static bool file_exists() {
    if (access(DB_NAME, F_OK) == 0) return true;
    return false;
}

// Function to check if any of the specified tables have data
bool has_data_in_tables(const char *tables[], int num_tables) {
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
bool mx_isdb_valid() {
    // Check if the database file exists
    if (!dir_exists(DB_DIR)) return false;
    // Check if the database file exists
    if (!file_exists()) return false;

    if (mx_db_init() < 0) return false;

    const char *tables[] = {"chats", "contacts", "messages", "settings"};
    int num_tables = 4;

    if (has_data_in_tables(tables, num_tables)) {
        logger_debug("database is valid\n");
        sqlite3_close(db);
        return true;
    }
    logger_debug("database is NOT valid\n");
    sqlite3_close(db);
    return false;
}

