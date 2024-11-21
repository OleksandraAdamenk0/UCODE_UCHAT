//
// Created by oleksandra on 21/11/24.
//

#include "data_exchange.h"

t_login_response *mx_login_response(char *str, int *status_ptr, char **msg_ptr) {
    *status_ptr = -1001;
    *msg_ptr = NULL;
    t_login_response *result = malloc(sizeof(t_login_response));
    if (!result) return NULL;

    result->tokens[0] = NULL;
    result->tokens[1] = NULL;

    cJSON *response = cJSON_Parse(str);
    if (!response) {
        cJSON_Delete(response);
        free(result);
        return NULL;
    }

    cJSON *msg = mx_get_json_item(response, "message", status_ptr, -1001);
    if (!msg) {
        cJSON_Delete(response);
        free(result);
        return NULL;
    }
    *msg_ptr = mx_strdup(msg->valuestring);

    cJSON *status = mx_get_json_item(response, "status", status_ptr, -1002);
    if (!status) {
        cJSON_Delete(response);
        free(result);
        return NULL;
    }

    *status_ptr = mx_atoi(status->valuestring);

    if (*status_ptr < 0) {
        cJSON_Delete(response);
        return result;
    }

    cJSON *access = NULL;
    cJSON *refresh = NULL;
    if (mx_get_tokens(response, &access, &refresh) < 0) {
        cJSON_Delete(response);
        return result;
    }

    result->tokens[0] = mx_strdup(access->valuestring);
    result->tokens[1] = mx_strdup(refresh->valuestring);

    cJSON_Delete(response);
    return result;
}
