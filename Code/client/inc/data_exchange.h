//
// Created by oleksandra on 21/11/24.
//

#ifndef CLIENT_DATA_EXCHANGE_H
#define CLIENT_DATA_EXCHANGE_H

#include "responses.h"
#include "cJSON.h"

int mx_handle_request(char *data, t_action action, t_response **response);

int mx_login(char *data, t_response **response);
int mx_registration(char *data, t_response **response);

int mx_get_chats(long long int id, t_response **response);
char *mx_get_last_message(long long int id);

#endif //CLIENT_DATA_EXCHANGE_H
