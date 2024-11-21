//
// Created by oleksandra on 10/11/24.
//

#ifndef UCODE_UCHAT_REQUEST_PROCESSING_H
#define UCODE_UCHAT_REQUEST_PROCESSING_H


#include "libmx.h"
#include "cJSON.h"
#include "cencode.h"
#include "cdecode.h"

int mx_registration_request(const cJSON *request);
cJSON *mx_registration_logic(const cJSON *request);
char *mx_registration_response(const int status, cJSON *response);

int mx_login_request(const cJSON *request);
cJSON *mx_login_logic(const cJSON *request);
char *mx_login_response(const int status, cJSON *response);

int mx_get_all_contacts_request(const cJSON *request);
cJSON *mx_get_all_contacts_logic(const cJSON *request);
char *mx_get_all_contacts_response(const int status, cJSON *response);

int mx_get_all_chats_request(const cJSON *request);
cJSON *mx_get_all_chats_logic(const cJSON *request);
char *mx_get_all_chats_response(const int status, cJSON *response);

int mx_get_msgs_request(const cJSON *request);
cJSON *mx_get_msgs_logic(const cJSON *request);
char *mx_get_msgs_response(const int status, cJSON *response);

#endif //UCODE_UCHAT_REQUEST_PROCESSING_H
