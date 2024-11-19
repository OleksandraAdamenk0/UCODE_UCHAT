#include <stdio.h>

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
    // cJSON *photo = cJSON_GetObjectItemCaseSensitive(request, "photo");

    printf("%s\n", username->valuestring);
    printf("%s\n", password->valuestring);
    printf("%s\n", phone->valuestring);
    printf("%s\n", email->valuestring);
    // printf("%s\n", photo->valuestring);

    sqlite3_bind_text(stmt, 1, username->valuestring, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password->valuestring, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, phone->valuestring, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, email->valuestring, -1, SQLITE_STATIC);
    // sqlite3_bind_text(stmt, 5, photo->valuestring, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -2;
    } else {
        printf("User  inserted successfully.\n");
    }

    sqlite3_finalize(stmt);
    return 0;
}
