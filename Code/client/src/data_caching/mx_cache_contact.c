#include "../../inc/data_caching.h"
#include "../../inc/client.h"

int mx_cache_contact(sqlite3 *db, t_get_contacts contact) {
    sqlite3_stmt *stmt;
    char *sql = "INSERT INTO contacts VALUES (?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, contact.username, -1, SQLITE_STATIC);

    if (contact.photo != NULL) {
        int photo_size = sizeof(contact.photo);
        unsigned char *photo_data = base64_decode(contact.photo, photo_size, &photo_size);

        if (photo_data != NULL) {
            sqlite3_bind_blob(stmt, 2, photo_data, photo_size, SQLITE_STATIC);
            free(photo_data);
        } else {
            logger_error("Failed to decode photo data.\n");
            sqlite3_finalize(stmt);
            return -1;
        }
    } else {
        // Bind NULL if no photo is provided
        sqlite3_bind_null(stmt, 2);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        char error[128];
        snprintf(error, sizeof(error), "Execution failed: %s\n", sqlite3_errmsg(db));
        logger_error(error);
        sqlite3_finalize(stmt);
        return -1;
    } else {
        logger_info("Contact saved successfully.\n");
    }

    return 0;
}
