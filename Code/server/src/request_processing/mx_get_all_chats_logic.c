//
// Created by oleksandra on 14/11/24.
//

#include "request_processing.h"

cJSON *mx_get_all_chats_logic(const cJSON *request) {
    cJSON *result = cJSON_CreateObject();

    cJSON *user_id_json = cJSON_GetObjectItem(request, "user_id");
    if (!user_id_json || !cJSON_IsString(user_id_json)) {
        // [add] log error
        cJSON_Delete(result);
        return NULL;
    }

    const char *user_id = user_id_json->valuestring;

    // GET FRON DB
    char *binary_data_1 = "photo";
    char *size_of_data_1 = mx_itoa(mx_strlen(binary_data_1));

    char *binary_data_2 = "photo";
    char *size_of_data_2 = mx_itoa(mx_strlen(binary_data_2));

    const char *db_chats[][4] = {
            {"12345", "Project Team", (const char *)binary_data_1, (const char *)size_of_data_1},
            {"67890", "John Doe", (const char *)binary_data_2, (const char *)size_of_data_2}
    };

    // GET FROM DB
    int chats_count = 2;

    cJSON_AddNumberToObject(result, "count", chats_count);

    cJSON *chats = cJSON_CreateArray();
    for (int i = 0; i < chats_count; ++i) {
        cJSON *chat = cJSON_CreateObject();
        cJSON_AddStringToObject(chat, "id", db_chats[i][0]);
        cJSON_AddStringToObject(chat, "name", db_chats[i][1]);

        unsigned char *photo_data = (unsigned char *)db_chats[i][2];
        size_t photo_size = (size_t)db_chats[i][3];

        if (!photo_data || photo_size == 0) {
            cJSON_AddStringToObject(chat, "photo", "");
            cJSON_AddItemToArray(chats, chat);
            continue;
        }

        // photo
        char *base64_photo = base64_encode(photo_data, photo_size);
        if (!base64_photo) {
            // log decoding error
            cJSON_AddStringToObject(chat, "photo", "");
            cJSON_AddItemToArray(chats, chat);
            continue;
        }
        cJSON_AddStringToObject(chat, "photo", base64_photo);
        free(base64_photo);

        cJSON_AddItemToArray(chats, chat);
    }
    cJSON_AddItemToObject(result, "chats", chats);
    return result;
}
