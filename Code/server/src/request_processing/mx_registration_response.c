//
// Created by oleksandra on 12/11/24.
//

#include "request_processing.h"

char *mx_registration_response(const int status, cJSON *response) {
    printf("forming response\n cjson response = %p\n", response);
    if (!response) response = cJSON_CreateObject();
    cJSON_AddStringToObject(response, "status", mx_itoa(status));

    if (status == 0) {
        cJSON_AddStringToObject(response, "message",
                                "Account created successfully.");
    } else if (status == -1) {
        cJSON_AddStringToObject(response, "message",
                                "Empty Username field.");
    } else if (status == -2) {
        cJSON_AddStringToObject(response, "message",
                                "Username already taken.");
    } else if (status == -3) {
        cJSON_AddStringToObject(response, "message",
                                "Password doesn't meet requirements.");
    } else if (status == -4) {
        cJSON_AddStringToObject(response,"message",
                                "Either a phone number or an email "
                                "has to be provided.");
    } else if (status == -5) {
        cJSON_AddStringToObject(response, "message",
                                "Invalid phone format.");
    } else if (status == -6) {
        cJSON_AddStringToObject(response, "message",
                                "Invalid email format.");
    } else if (status == -7) {
        cJSON_AddStringToObject(response, "message",
                                "Email is already registered.");
    } else if (status == -8) {
        cJSON_AddStringToObject(response, "message",
                                "Phone number is already registered.");
    } else {
        cJSON_ReplaceItemInObject(response, "status",
                                  cJSON_CreateString("-9"));
        cJSON_AddStringToObject(response, "message",
                                "Internal server error. Please try again later.");
    }

    char *response_str = cJSON_Print(response);
    cJSON_Delete(response);
    printf("status = %d; response_str = %s\n", status, response_str);
    return response_str;
}
