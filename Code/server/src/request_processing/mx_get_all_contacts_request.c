//
// Created by oleksandra on 13/11/24.
//

int mx_get_all_contacts(const cJSON *request) {
    cJSON *id = cJSON_GetObjectItemCaseSensitive(request, "user_id");

    if (!cJSON_IsString(id) || id->valuestring == NULL) {
        return -1;
    }

//    if (this user id wasn't found in db) {
//        return -1;
//    }

    return 0;
}
