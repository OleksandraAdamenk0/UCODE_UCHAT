//
// Created by oleksandra on 14/11/24.
//

#include "cJSON.h"

#include "request_processing.h"
#include "database_managment.h"
#include "requests.h"
#include "logger.h"


static t_registration *create_registration(const cJSON *request) {
    t_registration *result = malloc(sizeof(t_registration));

    result->username = cJSON_GetObjectItemCaseSensitive(request, "username")->valuestring;
    result->password = cJSON_GetObjectItemCaseSensitive(request, "password")->valuestring;

    cJSON *email = cJSON_GetObjectItemCaseSensitive(request, "email");
    if (email && email->valuestring) result->email = email->valuestring;
    else result->email = NULL;

    cJSON *phone = cJSON_GetObjectItemCaseSensitive(request, "phone");
    if (phone && phone->valuestring) result->phone = phone->valuestring;
    else result->phone = NULL;

    // photo
    cJSON *photo = cJSON_GetObjectItemCaseSensitive(request, "photo");
    if (photo && photo->valuestring) {
        char *decoded = NULL;
        mx_base64_decode(photo->valuestring, &decoded);
        if (decoded) result->photo = decoded;
        else result->photo = NULL;
    } else {
        result->photo = NULL;
    }
    return result;
}

static int get_access_token(char *username, char *password, char **access_token) {
    t_login *data = malloc(sizeof(t_login));
    data->password = password;
    data->username = username;
    int status = mx_get_user_id(data, access_token);
    free(data);
    if (status < 0) return -9;
    return 0;
}

static cJSON *add_access_token(cJSON **object, char *access_token) {
    cJSON *tokens = cJSON_CreateObject();
    cJSON_AddStringToObject(tokens, "access_token", access_token);
    cJSON_AddStringToObject(tokens, "refresh_token", "0");
    cJSON_AddItemToObject(*object, "tokens", tokens);
    return *object;
}

cJSON *mx_registration_logic(const cJSON *request, int *status) {
    logger_debug("mx_registration_logic started to work\n");
    cJSON *response = cJSON_CreateObject();
    t_registration *reg = create_registration(request);
    logger_debug("registration of the user started\n");

    status = mx_register_user(reg);

    char *msg = "registration of the user status: ";
    char *msg2 = mx_strjoin(msg, mx_itoa(status));
    msg = mx_strjoin(msg2, "\n");
    logger_debug(msg);
    free(msg);
    free(msg2);

    if (status == 0) {
        char *access_token;
        status = get_access_token(reg->username, reg->password, &access_token);
        char *msg = "getting token status: ";
        char *msg2 = mx_strjoin(msg, mx_itoa(status));
        msg = mx_strjoin(msg2, "\n");
        logger_debug(msg);
        free(msg);
        free(msg2);
        if (status == 0) add_access_token(&response, access_token);
    }
    free(reg);
    return response;
}
