//
// Created by oleksandra on 14/11/24.
//

#include <cjson/cJSON.h>

#include "request_processing.h"
#include "database_managment.h"

char *mx_registration_logic(sqlite3 *db, cJSON *request) {
    int status = mx_registration_request(request);

    if (status == 0) {
         status = mx_register_user(db, request);
    }

    cJSON *response = cJSON_CreateObject();
    char *response_str = mx_registration_response(status, response);
    cJSON_Delete(request);
    return response_str;
}
