#ifndef DATA_CACHING_H
#define DATA_CACHING_H

#include "sqlite3.h"
#include <stdio.h>
#include <stdbool.h>
#include "libmx.h"
#include "cdecode.h"
#include "cencode.h"

typedef struct {
    int id;
    int receiver;
    char *sender;
    char *timestamp;
    char *binary;
    char *message;
}       t_get_msgs;

typedef struct {
    char *username;
    char *photo;
}       t_get_contacts;

typedef struct {
    int chat_id;
    char *chat_name;
    char *last_message;
    char *photo;
}       t_get_chats;

typedef struct {
    char *email;
    char *phone;
    char *photo;
    char *theme;
}       t_get_settings;

void mx_create_client_tables(sqlite3 *db);
bool mx_is_database_valid(const char *db_path);
int mx_cache_settings(sqlite3 *db, t_get_settings settings);
int mx_cache_message(sqlite3 *db, t_get_msgs msg);
int mx_cache_contact(sqlite3 *db, t_get_contacts contact);
int mx_cache_chat(sqlite3 *db, t_get_chats chat);
t_list *mx_get_cached_chats(sqlite3 *db);
t_list *mx_get_cached_contacts(sqlite3 *db);

#endif //DATA_CACHING_H
