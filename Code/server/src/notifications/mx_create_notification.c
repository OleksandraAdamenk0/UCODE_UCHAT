#include "../../inc/notifications.h"

Notification mx_create_notification(NotificationType type, const char *sender, const char *content) {
    Notification notify;
    notify.type = type;
    mx_strncpy(notify.sender, sender, sizeof(notify.sender) - 1);
    mx_strncpy(notify.content, content, sizeof(notify.content) - 1);
    notify.timestamp = time(NULL);
    return notify;
}
