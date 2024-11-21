//
// Created by oleksandra on 19/11/24.
//

#include "request_processing.h"

int mx_get_msgs_request(const cJSON *request) {
    cJSON *id = cJSON_GetObjectItemCaseSensitive(request, "chat_id");

    if (!cJSON_IsString(id) || id->valuestring == NULL) {
        return -1;
    }
    return 0;
}
