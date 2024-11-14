//
// Created by oleksandra on 14/11/24.
//

#include "request_processing.h"

char *mx_get_all_contacts_handler(cJSON *request) {
    int status = mx_get_all_contacts_request(request);
    if (status == 0) {
        cJSON *result = mx_get_all_contacts_logic(request);
        if (!result) {
            // [add] log internal server error
            status = -9;
            char *response = mx_get_all_contacts_response(status, NULL);
        }
        char *response = mx_get_all_contacts_response(status, result);
    }
    char *response = mx_get_all_contacts_response(status, NULL);
    if (response == NULL) {
        logger_error("Error during forming a response"
                     " to the login request.\n");
        return NULL;
    }
    return response;
}