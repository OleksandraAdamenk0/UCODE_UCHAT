//
// Created by oleksandra on 14/11/24.
//

#include "request_processing.h"
#include "database.h"
#include "responses.h"
#include "logger.h"
#include "libmx.h"
#include "utils.h"

cJSON *mx_get_all_chats_logic(const cJSON *request, int *status) {
    cJSON *result = cJSON_CreateObject();
    const int user_id = (const int)(cJSON_GetNumberValue(cJSON_GetObjectItem(request, "user_id")));

    t_list *chats_list = mx_get_all_chats(user_id);
    if (!chats_list) {
        char *msg = mx_sprintf("No chats found for user %d\n", user_id);
        logger_error(msg);
        free(msg);
    }

    int chats_count = mx_list_size(chats_list);
    cJSON_AddNumberToObject(result, "count", chats_count);

    t_list *copy = chats_list;

    cJSON *chats = cJSON_CreateArray();
    for (int i = 0; i < chats_count && copy; ++i) {
        cJSON *chat = cJSON_CreateObject();
        cJSON_AddStringToObject(chat, "id", mx_itoa(((t_chat *)copy->data)->id));
        cJSON_AddStringToObject(chat, "name", ((t_chat *)copy->data)->name);

//        unsigned char *photo_data = (unsigned char *)db_chats[i][2];
//        size_t photo_size = (size_t)db_chats[i][3];
//
//        if (!photo_data || photo_size == 0) {
//            cJSON_AddStringToObject(chat, "photo", "");
//            cJSON_AddItemToArray(chats, chat);
//            continue;
//        }
//
//        // photo
//        char *base64_photo;
//        mx_base64_encode(photo_data, &base64_photo);
//        if (!base64_photo) {
//            // log decoding error
//            cJSON_AddStringToObject(chat, "photo", "");
//            cJSON_AddItemToArray(chats, chat);
//            continue;
//        }
//        cJSON_AddStringToObject(chat, "photo", base64_photo);
//        free(base64_photo);

        cJSON_AddItemToArray(chats, chat);
        copy = copy->next;
    }
    cJSON_AddItemToObject(result, "chats", chats);
    return result;
}
