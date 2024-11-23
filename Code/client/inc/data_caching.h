#ifndef DATA_CACHING_H
#define DATA_CACHING_H

#include <sqlite3.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int id;
    int receiver;
    char sender[64];
    char timestamp[64];
    char binary[256];
    char message[512];
}       t_get_msgs;

typedef struct {
    char username[64];
    char photo[256];
}       t_get_contacts;

typedef struct {
    int chat_id;
    char chat_name[128];
    char last_message[512];
    char photo[256];
}       t_get_chats;

typedef struct {
    char email[128];
    char phone[20];
    char photo[256];
    char theme[30];
}       t_get_settings;

void mx_create_client_tables(sqlite3 *db);
bool mx_is_database_valid(const char *db_path);

#endif //DATA_CACHING_H
