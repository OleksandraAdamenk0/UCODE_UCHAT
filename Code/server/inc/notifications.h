#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <time.h>
#include <sys/socket.h>
#include "cJSON.h"
#include "libmx.h"
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

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

Notification mx_create_notification(NotificationType type, const char *sender, const char *content);
char* mx_serialize_notification(Notification *notify);
void mx_send_notification(int client_socket, Notification *notify);

#endif
