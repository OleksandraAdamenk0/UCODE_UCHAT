#include "database.h"
#include "requests.h"
#include "logger.h"
#include "utils.h"

#define UNIQUE_USERNAME "UNIQUE constraint failed: users.username"
#define UNIQUE_PHONE "UNIQUE constraint failed: users.phone"
#define UNIQUE_EMAIL "UNIQUE constraint failed: users.email"


int mx_register_user(t_registration *data) {
    sqlite3_stmt *stmt;
    char *sql = "INSERT INTO users (username, password, email, phone, photo) VALUES (?, ?, ?, ?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return -9;
    }

    // Bind username
    if (sqlite3_bind_text(stmt, 1, data->username, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return -9;
    }

    // Bind password
    if (sqlite3_bind_text(stmt, 2, data->password, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return -9;
    }

    // Bind email
    if (data->email) {
        if (sqlite3_bind_text(stmt, 3, data->email, -1, SQLITE_STATIC) != SQLITE_OK) {
            char *msg = mx_sprintf("Error binding email: %s\n", sqlite3_errmsg(db));
            logger_error(msg);
            free(msg);
            sqlite3_finalize(stmt);
            return -9;
        }
    }

    // Bind phone
    if (data->phone) {
        if (sqlite3_bind_text(stmt, 4, data->phone, -1, SQLITE_STATIC) != SQLITE_OK) {
            char *msg = mx_sprintf("Error binding phone: %s\n", sqlite3_errmsg(db));
            logger_error(msg);
            free(msg);
            sqlite3_finalize(stmt);
            return -9;
        }
    }

    // Bind photo
    if (data->photo) {
        if (sqlite3_bind_blob(stmt, 5, data->photo, data->photo_size, SQLITE_STATIC) != SQLITE_OK) {
            char *msg = mx_sprintf("Error binding phone: %s\n", sqlite3_errmsg(db));
            logger_error(msg);
            free(msg);
            sqlite3_finalize(stmt);
            return -9;
        }
    }

    const char *expanded_sql = sqlite3_expanded_sql(stmt);
    if (expanded_sql) {
        char *msg = mx_sprintf("Expanded SQL: %s\n", expanded_sql);
        logger_debug(msg);
        free(msg);
        sqlite3_free((void *)expanded_sql);
    } else {
        char *msg = mx_sprintf("Failed to get expanded SQL: %s\n", sqlite3_errmsg(db));
        logger_debug(msg);
        free(msg);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        const char *error_msg = sqlite3_errmsg(db);
        char *msg = mx_sprintf("SQLite error: %s\n", error_msg);
        logger_error(msg);
        free(msg);

        if (mx_strcmp(UNIQUE_USERNAME, sqlite3_errmsg(db)) == 0) return -2;
        else if (mx_strcmp(UNIQUE_EMAIL, sqlite3_errmsg(db)) == 0) return -7;
        else if (mx_strcmp(UNIQUE_PHONE, sqlite3_errmsg(db)) == 0) return -8;
        else return -9;
    }

    sqlite3_finalize(stmt);
    return 0;
}
