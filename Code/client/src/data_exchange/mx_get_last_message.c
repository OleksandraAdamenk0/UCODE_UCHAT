//
// Created by oleksandra on 09/12/24.
//

#include "data_exchange.h"
#include "connection.h"
#include "responses.h"
#include "logger.h"
#include "libmx.h"
#include "cJSON.h"

#include <stdlib.h>

static char *get_request(long long int id) {
    cJSON *json = cJSON_CreateObject();
    if (!json) {
        logger_error("Failed to create JSON object for user settings request\n");
        return NULL;
    }

    cJSON_AddStringToObject(json, "action", "get_last_message");
    cJSON_AddNumberToObject(json, "user_id", id);

    char *json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    return json_str;
}

static char *parse_response(char *data) {
    if (!data) {
        logger_error("Response is NULL\n");
        return NULL;
    }
    cJSON *json = cJSON_Parse(data);
    if (!json) {
        logger_error("Failed to parse response JSON\n");
        return NULL;
    }
    cJSON *status = cJSON_GetObjectItemCaseSensitive(json, "status");
    if (!cJSON_IsNumber(status)) {
        logger_error("Response JSON does not contain a valid status\n");
        cJSON_Delete(json);
        return NULL;
    }

    if (status < 0) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON *msg = cJSON_GetObjectItemCaseSensitive(json, "message");
    if (!cJSON_IsString(msg)) {
        logger_error("Response JSON does not contain a valid message\n");
        return NULL;
    }

    char *result = mx_strdup(cJSON_GetStringValue(msg));
    cJSON_Delete(json);
    return result;
}

char *mx_get_last_message(long long int id) {
    char *request = get_request(id);
    if (!request) return NULL;
    if (mx_send_data(request) < 0) {
        logger_warn("mx_get_last_message: Failed sending request");
        free(request);
        return NULL;
    }
    free(request);
    char *received_data = NULL;
    if (mx_receive_data(&received_data) < 0) {
        logger_warn("mx_get_last_message: Failed receiving request");
        return NULL;
    }
    char *response = parse_response(received_data);
    free(received_data);
    if (!*response) return NULL;
    return 0;
}