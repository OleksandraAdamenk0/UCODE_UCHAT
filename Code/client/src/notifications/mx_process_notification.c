#include "../../inc/notifications.h"

void mx_process_notification(Notification *notify) {
    switch (notify->type) {
        case NOTIFY_MESSAGE:
            printf("New message from %s: %s\n", notify->sender, notify->content);
            break;
        case NOTIFY_TYPING:
            printf("%s is typing...\n", notify->sender);
            break;
        case NOTIFY_DELIVERED:
            printf("Your message to %s was delivered.\n", notify->sender);
            break;
        case NOTIFY_SEEN:
            printf("%s has seen your message.\n", notify->sender);
            break;
        case NOTIFY_CONTACT_ADDED:
            printf("New contact added: %s\n", notify->sender);
            break;
        default:
            printf("Unknown notification type.\n");
    }
}
