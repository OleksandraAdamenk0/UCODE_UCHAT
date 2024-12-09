#include "../../inc/notifications.h"

void mx_print_notification(Notification *notify) {
    printf("\n--- Notification ---\n");
    printf("Type: %d\n", notify->type);
    printf("Sender: %s\n", notify->sender);
    printf("Content: %s\n", notify->content);
    printf("Timestamp: %s\n", ctime(&notify->timestamp));
    printf("--------------------\n");
}
