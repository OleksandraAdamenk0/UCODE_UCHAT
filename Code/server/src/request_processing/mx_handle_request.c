//
// Created by oleksandra on 10/11/24.
//

#include "request_processing.h"
#include "server.h"

static void log_logic_error(char *action) {
    char *msg = "Internal server error during processing the \"";
    char *msg1 = mx_strjoin(msg, action);
    msg = mx_strjoin(msg1, "\" request.\n");
    logger_error(msg);
    free(msg);
    free(msg1);
}

static void log_response_error(char *action) {
    char *msg = "Error during forming a response to the ";
    char *msg1 = mx_strjoin(msg, action);
    msg = mx_strjoin(msg1, " request.\n");
    logger_error(msg);
    free(msg);
    free(msg1);
}

typedef int (*t_request_func)(const cJSON *);
typedef cJSON *(*t_logic_func)(const cJSON *, int *status);
typedef char *(*t_response_func)(int, cJSON *);

static char *handler(cJSON *request, t_request_func request_func,
                     t_logic_func logic_func, t_response_func response_func,
                     char *action) {
    logger_debug("Handler specified\n");

    int status = request_func(request);
    char *str_response = NULL;
    cJSON *response = NULL;

    if (status == 0) {
        if (!(response = logic_func(request, &status))) {
            log_logic_error(action);
            status = -9;
        }
    }
    str_response = response_func(status, response);
    if (!str_response) log_response_error(action);
    return str_response;
}

char *mx_handle_request(const char *request_str) {
    logger_debug("Handling request\n");
    cJSON *request = cJSON_Parse(request_str);
    if (!request) {
        logger_error("Invalid JSON format.\n");
        return NULL;
    }

    cJSON *action = cJSON_GetObjectItemCaseSensitive(request, "action");
    if (!cJSON_IsString(action) || action->valuestring == NULL) {
        logger_error("Missing or invalid action field.\n");
        cJSON_Delete(request);
        return NULL;
    }

    // specify handler
    char *response;
    if (mx_strcmp(action->valuestring, "register") == 0) {
        response = handler(request,
                           mx_registration_request,
                           mx_registration_logic,
                           mx_registration_response,
                           "register");
    } else if (mx_strcmp(action->valuestring, "login") == 0) {
        response = handler(request,
                           mx_login_request,
                           mx_login_logic,
                           mx_login_response,
                           "login");
    } else if (mx_strcmp(action->valuestring, "get_contacts") == 0) {
        response = handler(request,
                           mx_get_all_contacts_request,
                           mx_get_all_contacts_logic,
                           mx_get_all_contacts_response,
                           "get_contacts");
    } else if (mx_strcmp(action->valuestring, "get_chats") == 0) {
        response = handler(request,
                           mx_get_all_chats_request,
                           mx_get_all_chats_logic,
                           mx_get_all_chats_response,
                           "get_chats");
    } else if (mx_strcmp(action->valuestring, "get_messages") == 0) {
        response = handler(request,
                           mx_get_msgs_request,
                           mx_get_msgs_logic,
                           mx_get_msgs_response,
                           "get_messages");
    } else {
        logger_error("Unknown action requested.\n");
        response = mx_unknown_action_response(NULL);
    }
    cJSON_Delete(request);
    return response;
}
