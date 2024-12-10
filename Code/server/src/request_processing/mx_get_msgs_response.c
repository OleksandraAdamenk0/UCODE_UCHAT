//
// Created by oleksandra on 19/11/24.
//

#include "request_processing.h"
#include "libmx.h"

char *mx_get_msgs_response(const int status, cJSON *response) {
    cJSON_AddStringToObject(response, "status", mx_itoa(status));

    if (status == 0) {
        cJSON_AddStringToObject(response, "message",
                                "Messages retrieved successfully.");
    } else if (status == -1) {
        cJSON_AddStringToObject(response, "message",
                                "Invalid or missing token.");
    } else if (status == -2) {
        cJSON_AddStringToObject(response, "message",
                                "Chat not found.");
    } else {
        cJSON_ReplaceItemInObject(response, "status",cJSON_CreateString("-3"));
        cJSON_AddStringToObject(response, "message",
                                "Internal server error. Please try again later.");
    }

    char *response_str = cJSON_Print(response);
    cJSON_Delete(response);
    return response_str;
}
