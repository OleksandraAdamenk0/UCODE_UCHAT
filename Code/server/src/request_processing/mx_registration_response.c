//
// Created by oleksandra on 12/11/24.
//

#include "request_processing.h"

char *mx_registration_response(const int status) {
    if (status < -8) return NULL;
    cJSON *response = cJSON_CreateObject();
    if (!response) return NULL;

    cJSON_AddStringToObject(response, "status", mx_itoa(status));

    if (status == 0) {
        cJSON_AddStringToObject(response, "message",
                                "Account created successfully.");
        cJSON *tokens = cJSON_CreateObject();

        char *access_token = "get user id from db";
        cJSON_AddStringToObject(tokens, "access_token", access_token);

        cJSON_AddStringToObject(tokens, "refresh_token", "0");
        cJSON_AddItemToObject(response, "tokens", tokens);
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
    }

    char *response_str = cJSON_Print(response);
    cJSON_Delete(response);
    return response_str;
}
