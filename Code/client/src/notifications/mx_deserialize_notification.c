#include "../../inc/notifications.h"

Notification mx_deserialize_notification(const char *json_str) {
    Notification notify = {0};
    cJSON *json = cJSON_Parse(json_str);

    if (!json) {
        fprintf(stderr, "Error parsing JSON string\n");
        return notify;
    }

    notify.type = (NotificationType)cJSON_GetObjectItem(json, "type")->valueint;
    mx_strncpy(notify.sender, cJSON_GetObjectItem(json, "sender")->valuestring, sizeof(notify.sender) - 1);
    mx_strncpy(notify.content, cJSON_GetObjectItem(json, "content")->valuestring, sizeof(notify.content) - 1);
    notify.timestamp = (time_t)cJSON_GetObjectItem(json, "timestamp")->valuedouble;

    cJSON_Delete(json);
    return notify;
}
