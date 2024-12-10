//
// Created by oleksandra on 06/12/24.
//

#ifndef SERVER_REQUEST_PROCESSING_H
#define SERVER_REQUEST_PROCESSING_H

#include "cJSON.h"

typedef int (*t_request_func)(const cJSON *);
typedef cJSON *(*t_logic_func)(const cJSON *, int *status);
typedef char *(*t_response_func)(int, cJSON *);

char *mx_handle_request(const char *request_str);

int mx_registration_request(const cJSON *request);
cJSON *mx_registration_logic(const cJSON *request, int *status);
char *mx_registration_response(const int status, cJSON *response);

int mx_login_request(const cJSON *request);
cJSON *mx_login_logic(const cJSON *request, int *status);
char *mx_login_response(const int status, cJSON *response);

int mx_get_all_contacts_request(const cJSON *request);
cJSON *mx_get_all_contacts_logic(const cJSON *request, int *status);
char *mx_get_all_contacts_response(const int status, cJSON *response);

int mx_get_all_chats_request(const cJSON *request);
cJSON *mx_get_all_chats_logic(const cJSON *request, int *status);
char *mx_get_all_chats_response(const int status, cJSON *response);

int mx_get_msgs_request(const cJSON *request);
cJSON *mx_get_msgs_logic(const cJSON *request, int *status);
char *mx_get_msgs_response(const int status, cJSON *response);

char *mx_unknown_action_response(cJSON *response);

#endif //SERVER_REQUEST_PROCESSING_H
