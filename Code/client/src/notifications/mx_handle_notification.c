#include "../../inc/notifications.h"

void mx_handle_notification(const char *json_str) {
    Notification notify = mx_deserialize_notification(json_str);
    mx_print_notification(&notify); 
}
