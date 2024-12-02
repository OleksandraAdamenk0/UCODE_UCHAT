//
// Created by oleksandra on 21/11/24.
//

#include "client.h"
#include "data_exchange.h"
#include "responses.h"

int mx_handle_request(char *data, t_action action, t_response **response) {
    if (!data) return -100;
    if (!response) return -100;
    if (action == REGISTRATION) return mx_registration(data, response);
    if (action == LOGIN) return mx_login(data, response);
    // ...

    logger_error("unknown type of request was tried to form\n");
    return NULL;
}
