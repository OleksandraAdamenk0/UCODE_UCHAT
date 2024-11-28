#include "../../inc/database_managment.h"

int mx_register_user(sqlite3 *db, t_get_user user) {
    sqlite3_stmt *stmt;
    char *sql = "INSERT INTO users VALUES (?, ?, ?, ?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, user.username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, user.password, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, user.email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, user.phone, -1, SQLITE_STATIC);

    if (user.photo != NULL) {
        size_t photo_size = sizeof(user.photo);
        unsigned char *photo_data = base64_decode(user.photo, photo_size, &photo_size); // Implement this function

        if (photo_data != NULL) {
            sqlite3_bind_blob(stmt, 5, photo_data, photo_size, SQLITE_STATIC);
            free(photo_data);
        } else {
            logger_error("Failed to decode photo data\n");
            sqlite3_finalize(stmt);
            return -1;
        }
    } else {
        // Bind NULL if no photo is provided
        sqlite3_bind_null(stmt, 5);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Execution failed: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        sqlite3_finalize(stmt);
        if (mx_strcmp("UNIQUE constraint failed: users.username", sqlite3_errmsg(db)) == 0) {
            return -2;
        } else if (mx_strcmp("UNIQUE constraint failed: users.email", sqlite3_errmsg(db)) == 0) {
            return -7;
        } else if (mx_strcmp("UNIQUE constraint failed: users.phone", sqlite3_errmsg(db)) == 0) {
            return -8;
        }
    } else {
        logger_info("User  inserted successfully.\n");
    }

    sqlite3_finalize(stmt);
    return 0;
}
