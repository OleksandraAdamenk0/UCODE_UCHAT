#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <time.h>
#include "cJSON.h"
#include "libmx.h"

// #include <string.h> // temporally

typedef enum {
    NOTIFY_MESSAGE,       // na new message received
    NOTIFY_TYPING,        // a user is typing
    NOTIFY_DELIVERED,     // a message was delivered
    NOTIFY_SEEN,          // a message was read/seen
    NOTIFY_CONTACT_ADDED  // a new contact added
} NotificationType;

typedef struct {
    NotificationType type;
    char sender[50];       // sender
    char content[1024];    // content 
    time_t timestamp;      // creation time
} Notification;

void mx_handle_notification(const char *json_str);
Notification mx_deserialize_notification(const char *json_str);
void mx_process_notification(Notification *notify);
void mx_print_notification(Notification *notify);

#endif
