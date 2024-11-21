//
// Created by oleksandra on 19/11/24.
//

#include "request_processing.h"

cJSON *mx_get_msgs_logic(const cJSON *request) {
    cJSON *result = cJSON_CreateObject();

    cJSON *user_id_json = cJSON_GetObjectItem(request, "user_id");
    if (!user_id_json || !user_id_json->valuestring) {
        // [add] log error
        cJSON_Delete(result);
        return NULL;
    }

    const char *user_id = user_id_json->valuestring;

    // GET DATA FROM DB
    // ...
    int msgs_count = 2;  // GET FROM DB
    msgs_count = (msgs_count < 50)? msgs_count: 50;  // Костиль для майбутнього динамічного підвантаження

    for (int i = 0; i < msgs_count; ++i) {
        // write data to the json file
    }

    return result;

}
