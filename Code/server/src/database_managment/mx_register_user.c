#include "database_managment.h"

int mx_register_user(sqlite3 *db, const cJSON *request) {
    sqlite3_stmt *stmt;
    char *sql = "INSERT INTO users VALUES (?, ?, ?, ?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    cJSON *username = cJSON_GetObjectItemCaseSensitive(request, "username");
    cJSON *password = cJSON_GetObjectItemCaseSensitive(request, "password");
    cJSON *phone = cJSON_GetObjectItemCaseSensitive(request, "phone");
    cJSON *email = cJSON_GetObjectItemCaseSensitive(request, "email");
    cJSON *photo = cJSON_GetObjectItemCaseSensitive(request, "photo");

    sqlite3_bind_text(stmt, 1, username->valuestring, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password->valuestring, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, email->valuestring, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, phone->valuestring, -1, SQLITE_STATIC);

    if (photo != NULL) {
        size_t photo_size = sizeof(photo->valuestring);
        unsigned char *photo_data = base64_decode(photo->valuestring, photo_size, &photo_size); // Implement this function

        if (photo_data != NULL) {
            sqlite3_bind_blob(stmt, 5, photo_data, photo_size, SQLITE_STATIC);
            free(photo_data);
        } else {
            fprintf(stderr, "Failed to decode photo data.\n");
            sqlite3_finalize(stmt);
            return -1;
        }
    } else {
        // Bind NULL if no photo is provided
        sqlite3_bind_null(stmt, 5);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        if (mx_strcmp("UNIQUE constraint failed: users.username", sqlite3_errmsg(db)) == 0) {
            return -2;
        } else if (mx_strcmp("UNIQUE constraint failed: users.email", sqlite3_errmsg(db)) == 0) {
            return -7;
        } else if (mx_strcmp("UNIQUE constraint failed: users.phone", sqlite3_errmsg(db)) == 0) {
            return -8;
        }
    } else {
        printf("User  inserted successfully.\n");
    }

    sqlite3_finalize(stmt);
    return 0;
}
