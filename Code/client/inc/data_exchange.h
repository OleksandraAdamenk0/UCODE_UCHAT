//
// Created by oleksandra on 21/11/24.
//

#ifndef UCODE_UCHAT_MAIN_DATA_EXCHANGE_H
#define UCODE_UCHAT_MAIN_DATA_EXCHANGE_H




#include "cJSON.h"
#include "libmx.h"
#include "requests.h"
#include "responses.h"

// UTILS
cJSON *mx_get_json_item(cJSON *object, char *string,
                        int *status, int error);
int mx_get_tokens(cJSON *response, cJSON **access,
                  cJSON **refresh, int *status);

int mx_base64_encode(const char *input_str, char **encoded_str);
int mx_base64_decode(const char *encoded_str, char **decoded_str);

// REQUESTS
char *mx_get_chats_request(t_get_chats_request *data);
char *mx_get_contacts_request(t_get_contacts_request *data);
char *mx_registration_request(t_registration_request *data);
char *mx_login_request(t_login_request *data);

// RESPONSES
t_registration_response *mx_registration_response(char *str,int *status_ptr,
                                                  char **msg_ptr);
t_login_response *mx_login_response(char *str, int *status_ptr, char **msg_ptr);

#endif //UCODE_UCHAT_MAIN_DATA_EXCHANGE_H
