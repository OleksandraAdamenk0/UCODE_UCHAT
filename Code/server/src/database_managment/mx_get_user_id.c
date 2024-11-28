//
// Created by oleksandra on 26/11/24.
//

#include "database_managment.h"

int mx_get_user_id(t_login *data, char **user_id) {
    sqlite3_stmt *stmt;
    char *sql = "SELECT id FROM users WHERE username = ? AND password = ?";
    *user_id = NULL;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, data->username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, data->password, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *id = sqlite3_column_text(stmt, 0);
        *user_id = mx_strdup((const char *)id);
    } else return -2;

    sqlite3_finalize(stmt);
    return 0;
}
