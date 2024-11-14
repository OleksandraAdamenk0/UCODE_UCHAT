//
// Created by oleksandra on 13/11/24.
//

#include "request_processing.h"

int mx_login_request(cJSON *request) {
    cJSON *username = cJSON_GetObjectItemCaseSensitive(request, "username");
    cJSON *password = cJSON_GetObjectItemCaseSensitive(request, "password");

    if ((!cJSON_IsString(username) || username->valuestring == NULL)
        || (!cJSON_IsString(password) || password->valuestring == NULL) ){
        return -1;
    }

    // if (username doesn't exist in DB) {
    //    return -1;
    // }

    // if (password provided by client doesn't match password from the DB') {
    //    return -1;
    //}
    return 0;
}
