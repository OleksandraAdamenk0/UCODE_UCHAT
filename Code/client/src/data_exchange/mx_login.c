//
// Created by oleksandra on 01/12/24.
//
#include "data_exchange.h"
#include "connection.h"
#include "libmx.h"
#include "logger.h"
#include "client.h"
#include "utils.h"

static void internal_error_handling(int status, t_response **response) {
    if (status >= 0) {
        logger_debug("No format errors in registration request\n");
    } else if (status == -1) {
        (*response)->msg = "Empty username field.";
        logger_error("Username format error\n");
    } else if (status == -100) {
        (*response)->msg = "Internal error. Please try again later.";
        logger_error("Internal request handling error\n");
    } else {
        (*response)->msg = "Internal error. Please try again later.";
        logger_error("Unknown format error in login json\n");
    }
}

static int login_request(const char *data, char **request) {
    *request = NULL;
    cJSON *json = cJSON_Parse(data);
    if (!json) return -100;

    const char *fields[] = {"action", "username", "password"};
    cJSON *items[3];

    for (int i = 0; i < 3; i++) {
        items[i] = cJSON_GetObjectItemCaseSensitive(json, fields[i]);
        if (!cJSON_IsString(items[i]) || mx_strlen(items[i]->valuestring) == 0)
            items[i] = NULL;
    }

    if (!items[1] || !items[2] || !items[0]) {
        cJSON_Delete(json);
        return -1;
    }

    *request = cJSON_Print(json);
    cJSON_Delete(json);

    if (!*request) return -100;
    return 0;
}

static int get_tokens(t_response **result, cJSON *tokens) {
    cJSON *access_token = cJSON_GetObjectItemCaseSensitive(tokens, "access_token");
    cJSON *refresh_token = cJSON_GetObjectItemCaseSensitive(tokens, "refresh_token");

    if (!access_token || !refresh_token) return -1;

    t_login_response *data = malloc(sizeof(t_login_response));
    if (!data) return -1;

    data->tokens[0] = mx_strdup(access_token->valuestring);
    data->tokens[1] = mx_strdup(refresh_token->valuestring);

    if (!data->tokens[0] || !data->tokens[1]) {
        free(data);
        return -1;
    }
    (*result)->data = data;
    return 0;
}

static t_response *parse_response(char *responsestr, int *status) {
    *status = 0;
    cJSON *json = cJSON_Parse(responsestr);
    if (!json) {
        *status = -100;
        return NULL;
    }

    cJSON *jstatus = cJSON_GetObjectItemCaseSensitive(json, "status");
    cJSON *jmsg = cJSON_GetObjectItemCaseSensitive(json, "message");
    cJSON *tokens = cJSON_GetObjectItem(json, "tokens");

    if (!jstatus || !jmsg) {
        *status = -100;
        cJSON_Delete(json);
        return NULL;
    }

    t_response *result = malloc(sizeof(t_response));
    if (!result) {
        *status = -100;
        cJSON_Delete(json);
        return NULL;
    }

    result->action = LOGIN;
    result->status = mx_atoi(cJSON_GetStringValue(jstatus));
    result->msg = mx_strdup(jmsg->valuestring);
    result->data = NULL;
    if (!tokens) {
        cJSON_Delete(json);
        return result;
    }

    if (get_tokens(&result, tokens) < 0) {
        *status = -100;
        cJSON_Delete(json);
        free(result);
        return NULL;
    }
    cJSON_Delete(json);
    return result;
}

int mx_login(char *data, t_response **response) {
    int status;
    if (mode == 0) {  // online
        status = mx_send_data(data);
        if (status < 0) return status;
        char *responsestr = NULL;
        status = mx_receive_data(&responsestr);
        if (status < 0) {
            if (responsestr) free(responsestr);
            return status;
        }
        *response = parse_response(responsestr, &status);
    } else if (mode == -1) {  // offline

    } else {
        char *msg = mx_sprintf("App is running in unknown mode %d\n", mode);
        logger_warn(msg);
        free(msg);
    }
    return 0;
}
