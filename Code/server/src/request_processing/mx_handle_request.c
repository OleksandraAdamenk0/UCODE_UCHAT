//
// Created by oleksandra on 10/11/24.
//

#include "request_processing.h"

int handle_request(const char *request_str) {
    cJSON *request = cJSON_Parse(json_request);
    if (!request) {
        // error
    }

    cJSON *action = cJSON_GetObjectItemCaseSensitive(request, "action");
    if (!cJSON_IsString(action) || action->valuestring == NULL) {
        // error
    }

    // specify handler

}
