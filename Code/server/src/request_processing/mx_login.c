//
// Created by oleksandra on 14/11/24.
//

#include "request_processing.h"

char *mx_login_handler(cJSON *request) {
    int status = mx_login_request(request);
    if (status == 0) {
        cJSON *result = mx_login_logic(request);
        if (!result) {
            // [add] log internal server error
            status = -9;
            char *response = mx_login_response(status, NULL);
        }
        char *response = mx_login_response(status, result);
    }
    char *response = mx_login_response(status, NULL);
    if (response == NULL) {
        logger_error("Error during forming a response"
                     " to the login request.\n");
        return NULL;
    }
    return response;
}
