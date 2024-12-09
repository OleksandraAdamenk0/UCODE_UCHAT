#include "../../inc/notifications.h"

char* mx_serialize_notification(Notification *notify) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", notify->type);
    cJSON_AddStringToObject(json, "sender", notify->sender);
    cJSON_AddStringToObject(json, "content", notify->content);
    cJSON_AddNumberToObject(json, "timestamp", notify->timestamp);
    
    char *json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    return json_str;
}
