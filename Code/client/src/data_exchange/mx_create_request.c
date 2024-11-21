//
// Created by oleksandra on 21/11/24.
//

#include "client.h"
#include "data_exchange.h"

char *mx_create_request(t_request *data) {
    if (!data) return NULL;
    if (data->action == REGISTRATION) {
        t_registration_request *req = (t_registration_request *)data->data;
        char *result = mx_registration_request(req);
        if (!result)
            logger_error("error occurred "
                         "during the formation of registration request\n");
        return result;
    }

    if (data->action == LOGIN) {
        t_login_request *req = (t_login_request *)data->data;
        char *result = mx_login_request(req);
        if (!result)
            logger_error("error occurred "
                         "during the formation of login request\n");
        return result;
    }

    if (data->action == GET_CONTACTS) {
        t_get_contacts_request *req = (t_get_contacts_request *)data->data;
        char *result = mx_get_contacts_request(req);
        if (!result)
            logger_error("error occurred "
                         "during the formation of get contacts request\n");
        return result;
    }

    if (data->action == GET_CHATS) {
        t_get_chats_request *req = (t_get_chats_request *)data->data;
        char *result = mx_get_chats_request(req);
        if (!result)
            logger_error("error occurred "
                         "during the formation of get chats request\n");
        return result;
    }

    // ...

    logger_error("unknown type of request was tried to form\n");
    return NULL;
}
