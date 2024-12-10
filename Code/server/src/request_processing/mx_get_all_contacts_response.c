//
// Created by oleksandra on 14/11/24.
//

#include "request_processing.h"
#include "libmx.h"

char *mx_get_all_contacts_response(const int status, cJSON *response) {
    cJSON_AddStringToObject(response, "status", mx_itoa(status));

    if (status == 0) {
        cJSON_AddStringToObject(response, "message",
                                "Contacts retrieved successfully.");
    } else if (status == -1) {
        cJSON_AddStringToObject(response, "message",
                                "Invalid or missing user_id.");
    } else if (status == -2) {
        cJSON_AddStringToObject(response, "message",
                                "Invalid or missing token.");
    } else {
        cJSON_ReplaceItemInObject(response, "status",cJSON_CreateString("-3"));
        cJSON_AddStringToObject(response, "message",
                                "Internal server error. Please try again later.");
    }

    char *response_str = cJSON_Print(response);
    cJSON_Delete(response);
    return response_str;
}
