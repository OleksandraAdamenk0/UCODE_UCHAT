//
// Created by oleksandra on 14/11/24.
//

#include "request_processing.h"

char *mx_registration_handler(cJSON *request) {
    int status = mx_registration_request(request);

    if (status == 0) {
        cJSON *result = mx_registration_logic(request);
        if (!result) {
            // [add] log internal server errors
            status = -9;
            char *response = mx_registration_response(status, NULL);
        }

        char *response = mx_registration_response(status, result);
    }

    char *response = mx_registration_response(status, NULL);
    if (response == NULL) {
        // [add] log error during forming a response (add client id?)
        logger_error("Error during forming a response"
                     " to the registration request.\n");
        return NULL;
    }
    return response;
}