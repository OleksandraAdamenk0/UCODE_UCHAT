//
// Created by oleksandra on 09/12/24.
//

#include "data_exchange.h"
#include "connection.h"
#include "responses.h"
#include "logger.h"
#include "libmx.h"
#include "cJSON.h"

static char *get_request(long long int id) {
    cJSON *json = cJSON_CreateObject();
    if (!json) {
        logger_error("Failed to create JSON object for user settings request\n");
        return NULL;
    }

    cJSON_AddStringToObject(json, "action", "get_chats");
    cJSON_AddNumberToObject(json, "user_id", id);

    char *json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    return json_str;
}

static t_response *parse_response(char *data) {
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
    cJSON *msg = cJSON_GetObjectItemCaseSensitive(json, "message");
    if (!cJSON_IsNumber(status)) {
        logger_error("Response JSON does not contain a valid status\n");
        cJSON_Delete(json);
        return NULL;
    }

    t_response *response = malloc(sizeof(t_response));
    if (!response) {
        logger_error("Failed to allocate memory for response\n");
        cJSON_Delete(json);
        return NULL;
    }
    response->action = GET_CHATS;
    response->status = (int)cJSON_GetNumberValue(status);
    response->msg = msg && cJSON_IsString(msg) ? mx_strdup(cJSON_GetStringValue(msg)) : NULL;
    response->data = NULL;

    if (response->status < 0) {
        cJSON_Delete(json);
        return response;
    }

    // read chats amount from json create a structure to contain amount and chats,
    // write amount and chats to this structure add structure to the response->data

    cJSON *count_json = cJSON_GetObjectItemCaseSensitive(json, "count");
    cJSON *array = cJSON_GetObjectItemCaseSensitive(json, "chats");
    if (!cJSON_IsArray(array)) {
        logger_error("Response JSON does not contain a valid chats array\n");
        cJSON_Delete(json);
        response->status = -1;
        return response;
    }
    if (!cJSON_IsNumber(count_json)) {
        logger_error("Response JSON does not contain a valid counter\n");
        count_json = NULL;
    }

    int count = count_json && cJSON_IsNumber(count_json)
            ? (int)cJSON_GetNumberValue(count_json) : cJSON_GetArraySize(array);

    t_chats *chats_data = malloc(sizeof(t_chats));
    if (!chats_data) {
        logger_error("Failed to allocate memory for chats_data\n");
        cJSON_Delete(json);
        free(response);
        return NULL;
    }
    chats_data->count = count;
    chats_data->chats = malloc(sizeof(t_chat) * count);
    if (!chats_data->chats) {
        logger_error("Failed to allocate memory for chats\n");
        cJSON_Delete(json);
        free(chats_data);
        free(response);
        return NULL;
    }

    cJSON *chat = NULL;
    int i = 0;
    cJSON_ArrayForEach(chat, array) {
        cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(chat, "id");
        cJSON *chat_name = cJSON_GetObjectItemCaseSensitive(chat, "name");

        if (!cJSON_IsNumber(chat_id) || !cJSON_IsString(chat_name)) {
            logger_error("Invalid chat data in response\n");
            for (int j = 0; j < i; j++) free(chats_data->chats[j].name);
            free(chats_data->chats);
            free(chats_data);
            cJSON_Delete(json);
            return response;
        }

        chats_data->chats[i].id = (int)cJSON_GetNumberValue(chat_id);
        chats_data->chats[i].name = mx_strdup(cJSON_GetStringValue(chat_name));
        i++;
    }

    response->data = chats_data;
    cJSON_Delete(json);
    return response;
}

int mx_get_chats(long long int id, t_response **response) {
    char *request = get_request(id);
    if (!request) return -1;
    if (mx_send_data(request) < 0) {
        logger_warn("mx_get_chats: Failed sending request");
        free(request);
        return -2;
    }
    free(request);
    char *received_data = NULL;
    if (mx_receive_data(&received_data) < 0) {
        logger_warn("mx_get_chats: Failed receiving response");
        return -2;
    }

    *response = parse_response(received_data);
    free(received_data);
    if (!*response) return -3;
    return 0;
}
