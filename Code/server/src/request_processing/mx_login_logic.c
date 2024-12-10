//
// Created by oleksandra on 14/11/24.
//

#include "request_processing.h"
#include "database.h"
#include "security.h"
#include "logger.h"
#include "utils.h"

cJSON *mx_login_logic(const cJSON *request, int *status) {
    logger_debug("mx_login_logic check");

    cJSON *result = cJSON_CreateObject();
    if (!result) logger_warn("Failed create cJSON structure");
    else logger_debug("Created cJSON structure");

    cJSON *json_username = cJSON_GetObjectItemCaseSensitive(request, "username");
    cJSON *json_password = cJSON_GetObjectItemCaseSensitive(request, "password");

    char *username = cJSON_GetStringValue(json_username);
    char *password = cJSON_GetStringValue(json_password);

    cJSON *tokens = cJSON_CreateObject();

    int id = mx_get_user_id(username, USERNAME);
    if (id < 1) {
        char *msg = mx_sprintf("Got error code from mx_get_user_id: %d", id);
        logger_error(msg);
        free(msg);
        *status = -1;
        return result;
    }
    logger_debug("got user id");
    logger_debug(mx_itoa(id));
    *status = mx_check_password(id, password);
    if (*status < 0) return result;
    char *access_token = mx_itoa(id);
    cJSON_AddStringToObject(tokens, "access_token", access_token);

    cJSON_AddStringToObject(tokens, "refresh_token", "0");
    cJSON_AddItemToObject(result, "tokens", tokens);

    return result;
}
