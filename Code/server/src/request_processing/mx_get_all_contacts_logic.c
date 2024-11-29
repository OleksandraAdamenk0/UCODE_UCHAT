//
// Created by oleksandra on 14/11/24.
//

#include "request_processing.h"

cJSON *mx_get_all_contacts_logic(const cJSON *request, int *status) {
    cJSON *result = cJSON_CreateObject();

    cJSON *user_id_json = cJSON_GetObjectItem(request, "user_id");
    if (!user_id_json || !cJSON_IsString(user_id_json)) {
        cJSON_Delete(result);
        return NULL;
    }

    const char *user_id = user_id_json->valuestring;

    // GET FRON DB
    char *binary_data_1 = "photo";
    char *size_of_data_1 = mx_itoa(mx_strlen(binary_data_1));

    char *binary_data_2 = "photo";
    char *size_of_data_2 = mx_itoa(mx_strlen(binary_data_2));

    const char *db_contacts[][4] = {
            {"12345", "Alice Smith", (const char *)binary_data_1, (const char *)size_of_data_1},
            {"67890", "Bob Johnson", (const char *)binary_data_2, (const char *)size_of_data_2}
    };

    // GET FROM DB
    int contact_count = 2;

    cJSON_AddNumberToObject(result, "count", contact_count);

    cJSON *contacts = cJSON_CreateArray();
    for (int i = 0; i < contact_count; i++) {
        cJSON *contact = cJSON_CreateObject();
        cJSON_AddStringToObject(contact, "id", db_contacts[i][0]);
        cJSON_AddStringToObject(contact, "name", db_contacts[i][1]);

        unsigned char *photo_data = (unsigned char *)db_contacts[i][2];
        size_t photo_size = (size_t)db_contacts[i][3];

        if (!photo_data || photo_size == 0) {
            cJSON_AddStringToObject(contact, "photo", "");
            cJSON_AddItemToArray(contacts, contact);
            continue;
        }

        // photo
        char *base64_photo = base64_encode(photo_data, photo_size);
        if (!base64_photo) {
            // log decoding error
            cJSON_AddStringToObject(contact, "photo", "");
            cJSON_AddItemToArray(contacts, contact);
            continue;
        }
        cJSON_AddStringToObject(contact, "photo", base64_photo);
        free(base64_photo);

        cJSON_AddItemToArray(contacts, contact);
    }

    cJSON_AddItemToObject(result, "contacts", contacts);
    return result;
}
