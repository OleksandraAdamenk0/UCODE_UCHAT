#ifndef DATA_CACHING_H
#define DATA_CACHING_H

#include <sqlite3.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>

#define DB_DIR "client/db"
#define DB_NAME DB_DIR "/app.db"

extern sqlite3 *db;

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
t_list *mx_get_cached_messages_from_chat(sqlite3 *db, int chat_id);
t_get_settings *mx_get_cached_settings(sqlite3 *db);

int mx_update_settings_email(sqlite3 *db, char *new_email, char *old_email);
int mx_update_chat_name(sqlite3 *db, char *new_chat_name, int chat_id);
int mx_update_chat_photo(sqlite3 *db, char *new_chat_photo, int photo_size, int chat_id);
int mx_update_message_text(sqlite3 *db, char *new_message_text, int id);
int mx_update_settings_phone(sqlite3 *db, char *new_phone, char *old_phone);
int mx_update_settings_photo(sqlite3 *db, char *new_photo, int new_photo_size, char *old_photo, int old_photo_size);
int mx_update_settings_theme(sqlite3 *db, char *new_theme, char *old_theme);

int mx_delete_cached_message(sqlite3 *db, int message_id);
int mx_delete_cached_contact(sqlite3 *db, char *username);
int mx_delete_cached_chat(sqlite3 *db, int chat_id);

#endif //DATA_CACHING_H
