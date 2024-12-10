#include "data_caching.h"
#include "logger.h"
#include "utils.h"
#include "libmx.h"

#include <sys/stat.h>

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

static int has_data_in_tables(const char *tables[], int num_tables) {
    for (int i = 0; i < num_tables; i++) {
        char *sql = mx_sprintf("SELECT * FROM %s", tables[i]);

        sqlite3_stmt *stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        mx_strdel(&sql);
        if (rc != SQLITE_OK) return -1;

        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        // true, at least one table has data
        if (rc == SQLITE_ROW) {
            if (sqlite3_column_int(stmt, 0) > 0) return 0;
        } else return -1;  // Error in executing the statement
    }
    return -1;
}

int mx_is_db_valid() {
    // Check if the database file exists
    if (!dir_exists(DB_DIR)) return -1;
    // Check if the database file exists
    if (!file_exists()) return -1;

    const char *tables[] = {"chats", "contacts", "messages", "settings"};
    int num_tables = 4;

    int status = has_data_in_tables(tables, num_tables);
    sqlite3_close(db);

    if (status < 0) logger_debug("database is not valid\n");
    else logger_debug("database is valid\n");

    return (status < 0)? -1: 0;
}
