//
// Created by oleksandra on 21/11/24.
//

#include "data_exchange.h"

cJSON *mx_get_json_item(cJSON *object, char *string,
                       int *status, int error) {
    cJSON *item = cJSON_GetObjectItemCaseSensitive(object, string);
    if (!cJSON_IsString(item)) {
        *status = error;
        return NULL;
    }
    return item;
}
