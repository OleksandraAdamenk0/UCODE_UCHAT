//
// Created by oleksandra on 01/12/24.
//
#include "data_exchange.h"
#include "connection.h"
#include "responses.h"
#include "logger.h"

static void internal_error_handling(int status, t_response **response) {
    if (status >= 0) {
        logger_debug("No format errors in registration request\n");
    } else if (status == -1) {
        (*response)->msg = "Empty username field.";
        logger_error("Username format error\n");
    } else if (status == -3) {
        (*response)->msg = "Password doesn\\'t meet requirements.<br>"
                           "Password must meet the following requirements:<br>"
                           "<ul><li>At least 8 characters</li>"
                           "<li>At least one uppercase letter</li>"
                           "<li>At least one lowercase letter</li>"
                           "<li>At least one digit</li>"
                           "<li>At least one of the following special characters: !@#$*-_?.</li>"
                           "</ul>"
                           "Only these special characters are allowed: !@#$*-_?.";
        logger_error("Password format error</br>");
    } else if (status == -4) {
        (*response)->msg = "Either a phone number or an email has to be provided.";
        logger_error("Email / Phone format error\n");
    } else if (status == -100) {
        (*response)->msg = "Internal error. Please try again later.";
        logger_error("Internal request handling error\n");
    } else {
        (*response)->msg = "Internal error. Please try again later.";
        logger_error("Unknown format error in registration json\n");
    }
}

static int registration_request(const char *data, char **request) {
    *request = NULL;
    cJSON *json = cJSON_Parse(data);
    if (!json) return -100;

    const char *fields[] = {"action", "username", "password", "email", "phone"};
    cJSON *items[5];

    for (int i = 0; i < 5; i++) {
        items[i] = cJSON_GetObjectItemCaseSensitive(json, fields[i]);
        if (!cJSON_IsString(items[i]) || mx_strlen(items[i]->valuestring) == 0)
            items[i] = NULL;
    }

    if (!items[1] || !items[2] || !items[0] || (!items[3] && !items[4]))
        cJSON_Delete(json);
    if (!items[1]) return -1;
    if (!items[2]) return -3;
    if (!items[3] && !items[4]) return -4;

    *request = cJSON_Print(json);
    cJSON_Delete(json);

    if (!*request) return -100;
    return 0;
}


static int get_tokens(t_response **result, cJSON *tokens) {
    cJSON *access_token = cJSON_GetObjectItemCaseSensitive(tokens, "access_token");
    cJSON *refresh_token = cJSON_GetObjectItemCaseSensitive(tokens, "refresh_token");

    if (!access_token || !refresh_token) return -1;

    t_registration_response *data = malloc(sizeof(t_registration_response));
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

static t_response *registration_response(char *responsestr, int *status) {
    *status = 0;
    printf("%s\n", responsestr);
    cJSON *json = cJSON_Parse(responsestr);
    if (!json) {
        *status = -100;
        return NULL;
    }

    cJSON *jstatus = cJSON_GetObjectItemCaseSensitive(json, "status");
    cJSON *jmsg = cJSON_GetObjectItemCaseSensitive(json, "message");

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

    result->action = REGISTRATION;
    result->status = mx_atoi(jstatus->valuestring);
    result->msg = mx_strdup(jmsg->valuestring);
    result->data = NULL;
    printf("status = %d\n", result->status);

    if (result->status == 0) {
        cJSON *tokens = cJSON_GetObjectItem(json, "tokens");
        if (get_tokens(&result, tokens) < 0) {
            *status = -100;
            cJSON_Delete(json);
            free(result);
            return NULL;
        }
    }

    cJSON_Delete(json);
    return result;
}

int mx_registration(char *data, t_response **response) {
    char *request;

    int status = registration_request(data, &request);

    internal_error_handling(status, response);
    (*response)->status = status;
    (*response)->action = REGISTRATION;

    if (status < 0) return status;

    status = mx_send_data(request);
    free(request);
    if (status < 0) return -100;

    char *responsestr = NULL;
    status = mx_receive_data(&responsestr);
    if (status < 0) {
        if (responsestr) free(responsestr);
        return -100;
    }

    *response = registration_response(responsestr, &status);
    printf("execution status = %d\n", status);

    printf("status = %d\n", (*response)->status);
    if (status < 0) return -100;
    return 0;
}