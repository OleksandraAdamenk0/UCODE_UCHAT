#include "../../inc/database_managment.h"

void mx_create_tables(sqlite3 *db) {
    char *errMsg = 0;

    const char *sql_users =
        "CREATE TABLE IF NOT EXISTS Users (" \
        "user_id INTEGER PRIMARY KEY AUTOINCREMENT," \
        "username TEXT NOT NULL," \
        "password TEXT NOT NULL," \
        "email TEXT," \
        "phone TEXT);";

    if (sqlite3_exec(db, sql_users, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Users table created successfully.\n");
    }
}
