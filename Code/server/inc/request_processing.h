//
// Created by oleksandra on 10/11/24.
//

#ifndef UCODE_UCHAT_REQUEST_PROCESSING_H
#define UCODE_UCHAT_REQUEST_PROCESSING_H


#include "libmx.h"
#include "cJSON.h"

int mx_registration_request(const cJSON *request);
char *mx_registration_response(const int status);

int mx_login_request(cJSON *request);


#endif //UCODE_UCHAT_REQUEST_PROCESSING_H
