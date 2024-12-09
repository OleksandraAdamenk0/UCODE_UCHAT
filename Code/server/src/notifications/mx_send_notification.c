#include "../../inc/notifications.h"

void mx_send_notification(int client_socket, Notification *notify) {
    char *json = mx_serialize_notification(notify);
    send(client_socket, json, mx_strlen(json), 0);
    free(json);
}
