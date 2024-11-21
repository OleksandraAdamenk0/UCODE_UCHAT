//
// Created by oleksandra on 21/11/24.
//

#include "data_exchange.h"

int mx_get_tokens(cJSON *response, cJSON **access, cJSON **refresh) {
    cJSON *tokens;
    if (!(tokens = mx_get_json_item(response, "tokens", status_ptr, -1003)))
        return -1;
    if (!(*access = mx_get_json_item(tokens, "access_token", status_ptr, -1004)))
        return -1;
    if (!(*refresh = mx_get_json_item(tokens, "refresh_token", status_ptr, -1005)))
        return -1;
    return 0;
}
