//
// Created by oleksandra on 14/11/24.
//

#include "request_processing.h"

int mx_get_all_chats_request(const cJSON *request) {
    cJSON *id = cJSON_GetObjectItemCaseSensitive(request, "user_id");

    if (!cJSON_IsString(id) || id->valuestring == NULL) {
        return -1;
    }

//    if (this user id wasn't found in db) {
//        return -1;
//    }

    return 0;
}
