#include "../../inc/database_managment.h"

void mx_add_user(sqlite3 *db, cJSON *request) {
    char *errMsg = 0;
    char sql[512];

    cJSON *username = cJSON_GetObjectItem(request, "username");
    cJSON *password = cJSON_GetObjectItem(request, "password");
    cJSON *email = cJSON_GetObjectItem(request, "email");
    cJSON *phone = cJSON_GetObjectItem(request, "phone");

    snprintf(sql, sizeof(sql), "INSERT INTO Users (username, password, email, phone) VALUES ('%s', '%s', '%s', '%s')",
        username->string, password->string, email->string, phone->string);

    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("User hasn't been added\n", username->string);
    }
}
