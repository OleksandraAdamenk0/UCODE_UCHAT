//
// Created by oleksandra on 14/11/24.
//

#include "cJSON.h"

#include "request_processing.h"
#include "database_managment.h"
#include "requests.h"
#include "logger.h"


static t_registration *json_to_struct(const cJSON *request) {
    t_registration *result = malloc(sizeof(t_registration));

    result->username = mx_strdup(cJSON_GetObjectItemCaseSensitive(request,"username")->valuestring);
    result->password = mx_strdup(cJSON_GetObjectItemCaseSensitive(request, "password")->valuestring);

    cJSON *email = cJSON_GetObjectItemCaseSensitive(request, "email");
    if (email && email->valuestring) result->email = mx_strdup(email->valuestring);
    else result->email = NULL;

    cJSON *phone = cJSON_GetObjectItemCaseSensitive(request, "phone");
    if (phone && phone->valuestring) result->phone = mx_strdup(phone->valuestring);
    else result->phone = NULL;

    // photo
    result->photo = NULL;
    cJSON *photo = cJSON_GetObjectItemCaseSensitive(request, "photo");
    if (photo && photo->valuestring) {
        char *decoded = NULL;
        result->photo_size = mx_base64_decode(photo->valuestring, &decoded);
        if (decoded) result->photo = decoded;
    }
    return result;
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
    t_registration *data = json_to_struct(request);
    logger_debug("registration of the user started\n");

    if ((*status = mx_register_user(data)) == 0) {
        logger_debug("user was registered successfully\n");
        int id = mx_get_user_id(data->username, USERNAME);
        if (id < 1) *status = -9;
        else {
            char *access_token = mx_itoa(id);
            logger_debug("successfully got access token\n");
            add_access_token(&response, access_token);
        }
    }
    free(data->username);
    free(data->password);
    if (data->email) free(data->email);
    if (data->phone) free(data->phone);
    if (data->photo) free(data->photo);
    free(data);
    return response;
}
