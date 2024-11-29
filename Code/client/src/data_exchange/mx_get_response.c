//
// Created by oleksandra on 21/11/24.
//

#include "client.h"
#include "data_exchange.h"

t_response *mx_get_response(t_api_type type, char *str) {
    t_response *result = malloc(sizeof(t_response));
    result->status = 1000;
    result->msg = NULL;
    result->data = NULL;

    if (type == REGISTRATION) {
        t_registration_response *data = mx_registration_response(str, &result->status, &result->msg);
        if (result->status == 0 && data) result->data = data;
        return result;
    }

    if (type == LOGIN) {
        t_login_response *data = mx_login_response(str, &result->status, &result->msg);
        if (result->status == 0 && data) result->data = data;
        return result;
    }
    // ...

    logger_error("unknown type of response was received\n");
    return NULL;
}
