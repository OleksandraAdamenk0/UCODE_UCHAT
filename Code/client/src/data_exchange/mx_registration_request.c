//
// Created by oleksandra on 21/11/24.
//

#include "data_exchange.h"

char *mx_registration_request(t_registration_request *data) {
    cJSON *request = cJSON_CreateObject();
    cJSON_AddStringToObject(request, "action", data->action);
    cJSON_AddStringToObject(request, "username", data->username);
    cJSON_AddStringToObject(request, "password", data->password);
    cJSON_AddStringToObject(request, "email", data->email);
    cJSON_AddStringToObject(request, "phone", data->phone);

    char *req_str = cJSON_Print(request);
    cJSON_Delete(request);
    return req_str;
}
