//
// Created by oleksandra on 10/11/24.
//

#ifndef UCODE_UCHAT_REQUEST_PROCESSING_H
#define UCODE_UCHAT_REQUEST_PROCESSING_H


#include "libmx.h"
#include "cJSON.h"
#include "sqlite3.h"

int mx_registration_request(const cJSON *request);
char *mx_registration_logic(sqlite3 *db, cJSON *request);
char *mx_registration_response(const int status, cJSON *response);

#endif //UCODE_UCHAT_REQUEST_PROCESSING_H