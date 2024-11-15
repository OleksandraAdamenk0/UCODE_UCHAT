//
// Created by oleksandra on 10/11/24.
//

#include "request_processing.h"
#include "server.h"

typedef int (*RequestFunction)(const cJSON *);
typedef cJSON *(*LogicFunction)(const cJSON *);
typedef char *(*ResponseFunction)(int, cJSON *);

static char *handler(cJSON *request,
                         RequestFunction request_func,
                         LogicFunction logic_func,
                         ResponseFunction response_func,
                         char *action) {
    int status = request_func(request);
    char *response = NULL;

    if (status == 0) {
        cJSON *result = logic_func(request);
        if (!result) {
            char *msg = "Internal server error during processing the \"";
            char *msg1 = mx_strjoin(msg, action);
            msg = mx_strjoin(msg1, "\" request.\n");
            logger_error(msg);
            free(msg);
            free(msg1);
            status = -9;
        }
        response = response_func(status, result);
    } else {
        response = response_func(status, NULL);
    }

    if (response == NULL) {
        char *msg = "Error during forming a response to the ";
        char *msg1 = mx_strjoin(msg, action);
        msg = mx_strjoin(msg1, " request.\n");
        logger_error(msg);
        free(msg);
        free(msg1);
        return NULL;
    }
    return response;
}


/**
 * @brief Handles incoming JSON-encoded requests, determines the action type,
 *        and delegates to the appropriate request handler. Constructs a JSON
 *        response based on the result and logs any errors encountered.
 *
 * @param request_str A string representing the JSON-encoded request from the client.
 * @return char* A JSON-encoded response string.
 *         - Returns a valid JSON response string if the request is handled successfully.
 *         - Returns NULL if an error occurs during parsing, validation, or response formation.
 *
 * @details
 * - The function performs the following steps:
 *   1. Parses the `request_str` using `cJSON_Parse`.
 *      - Logs an error and returns NULL if the JSON format is invalid.
 *   2. Validates the `action` field.
 *      - Logs an error and returns NULL if the `action` field is missing or invalid.
 *   3. Determines the action type:
 *      - If the `action` is "register", it calls `mx_registration_request` to handle the
 *        registration and `mx_registration_response` to form the response.
 *        - Logs an error and returns NULL if response formation fails.
 *      - Future handlers (e.g., "login") will be added as needed.
 *   4. Cleans up by deleting the parsed `cJSON` object to free memory.
 *
 * @note Logging:
 * - Logs "Invalid JSON format" if the JSON cannot be parsed.
 * - Logs "Missing or invalid action field" if the `action` field is incorrect.
 * - Logs "Error during forming a response" if response creation fails.
 *
 * @example
 * char *response = handle_request("{\"action\": \"register\", \"username\": \"user\", \"password\": \"Pass123!\"}"); \n
 * if (response) { \n
 *          // Use the response, then free it when done \n
 *          free(response); \n
 * }
 */
char *handle_request(const char *request_str) {
    cJSON *request = cJSON_Parse(request_str);
    if (!request) {
        logger_error("Invalid JSON format.\n");
        return NULL;
    }

    cJSON *action = cJSON_GetObjectItemCaseSensitive(request, "action");
    if (!cJSON_IsString(action) || action->valuestring == NULL) {
        logger_error("Missing or invalid action field.\n");
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
    }
    // ...

    cJSON_Delete(request);
    return response;
}
