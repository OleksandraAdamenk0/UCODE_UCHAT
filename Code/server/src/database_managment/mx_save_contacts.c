#include "server.h"
#include "database_managment.h"

int mx_save_contact(sqlite3 *db, t_get_contacts contact) {
    sqlite3_stmt *stmt;
    char *sql = "INSERT OR IGNORE INTO contacts VALUES (?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, contact.username, -1, SQLITE_STATIC);

    if (contact.photo != NULL) {
        int photo_size = sizeof(contact.photo);
        sqlite3_bind_blob(stmt, 2, contact.photo, photo_size, SQLITE_STATIC);
    } else {
        sqlite3_bind_null(stmt, 2);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        char error[128];
        snprintf(error, sizeof(error), "Contact caching failed: %s\n", sqlite3_errmsg(db));
        logger_error(error);
        sqlite3_finalize(stmt);
        return -1;
    } else {
        logger_info("Contact saved successfully.\n");
    }

    sqlite3_finalize(stmt);
    return 0;
}
