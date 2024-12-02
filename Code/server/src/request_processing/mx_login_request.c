//
// Created by oleksandra on 13/11/24.
//

#include "request_processing.h"

int mx_login_request(const cJSON *request) {
    cJSON *username = cJSON_GetObjectItemCaseSensitive(request, "username");
    cJSON *password = cJSON_GetObjectItemCaseSensitive(request, "password");

    if ((!cJSON_IsString(username) || username->valuestring == NULL) ||
    (!cJSON_IsString(password) || password->valuestring == NULL) ||
    mx_strlen(username->valuestring) == 0 ||
    mx_strlen(password->valuestring) == 0){
        return -1;
    }
    return 0;
}
