//
// Created by oleksandra on 13/11/24.
//

#include "request_processing.h"
#include "logger.h"

char *mx_login_response(const int status, cJSON *response) {
    cJSON_AddStringToObject(response, "status", mx_itoa(status));

    if (status == 0) {
        cJSON_AddStringToObject(response, "message",
                                "Login successful.");

    } else if (status == -1) {
        cJSON_AddStringToObject(response, "message",
                                "Invalid username or password.");

    } else {
        cJSON_ReplaceItemInObject(response, "status",cJSON_CreateString("-2"));
        cJSON_AddStringToObject(response, "message",
                                "Internal server error. Please try again later.");
    }

    char *response_str = cJSON_Print(response);
    cJSON_Delete(response);
    return response_str;
}
