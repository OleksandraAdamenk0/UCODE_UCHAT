#include "server.h"
#include "database_managment.h"

int save_settings(sqlite3 *db, t_add_settings *user_settings) {
    sqlite3_stmt *stmt;
    char *sql = "INSERT INTO settings (user_id, theme, email, phone, photo) VALUES (?, ?, ?, ?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    if (mx_strcmp(user_settings->theme, "light") != 0 && mx_strcmp(user_settings->theme, "dark") != 0) {
        fprintf(stderr, "Invalid theme value: %s\n", user_settings->theme);
        sqlite3_finalize(stmt);
        return -2;
    }

    if(mx_strcmp(user_settings->user_id, "") == 0) {
        fprintf(stderr, "Invalid or missing user_id %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -3;
    }

    if (mx_strcmp(user_settings->email, "") == 0 && mx_strcmp(user_settings->phone, "") == 0) {
        fprintf(stderr, "Either email or phone must be provided.\n");
        return -4;
    }

    sqlite3_bind_text(stmt, 1, user_settings->user_id, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, user_settings->theme, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, user_settings->email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, user_settings->phone, -1, SQLITE_STATIC);

    if (mx_strlen(user_settings->photo) > 0) {
        sqlite3_bind_text(stmt, 5, user_settings->photo, -1, SQLITE_STATIC);
    } else {
        sqlite3_bind_null(stmt, 5);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        char err_msg[256];
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        sqlite3_finalize(stmt);
        return -1;
    }
    else {
         logger_info("Settings saved successfully.\n");
    }

    sqlite3_finalize(stmt);
    mx_printstr("Settings saved successfully.\n");
    return 0;
}
