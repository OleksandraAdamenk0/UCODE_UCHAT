//
// Created by oleksandra on 28/11/24.
//

#include "request_processing.h"

char *mx_unknown_action_response(cJSON *response) {
    if (!response) response = cJSON_CreateObject();
    cJSON_AddStringToObject(response, "status", "-9");
    cJSON_AddStringToObject(response, "message","Unknown action.");
    char *response_str = cJSON_Print(response);
    cJSON_Delete(response);
    return response_str;
}
