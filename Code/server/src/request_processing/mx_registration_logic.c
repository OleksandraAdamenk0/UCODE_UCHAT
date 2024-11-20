//
// Created by oleksandra on 14/11/24.
//

#include "request_processing.h"

cJSON *mx_registration_logic(const cJSON *request) {
    // write username, password, email and/or phone to the db

    cJSON *result = cJSON_CreateObject();
    cJSON *tokens = cJSON_CreateObject();

    char *access_token = "get user id from db";
    cJSON_AddStringToObject(tokens, "access_token", access_token);

    cJSON_AddStringToObject(tokens, "refresh_token", "0");
    cJSON_AddItemToObject(result, "tokens", tokens);

    return result;
}
