#ifndef DATA_CACHING_H
#define DATA_CACHING_H

#include <sqlite3.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>

#define DB_DIR "client/db"
#define DB_NAME DB_DIR "/app.db"

extern sqlite3 *db;

void mx_create_client_tables(sqlite3 *db);
bool mx_is_database_valid(const char *db_path);
int mx_cache_settings(sqlite3 *db, t_get_settings settings);
int mx_cache_message(sqlite3 *db, t_get_msgs msg);
int mx_cache_contact(sqlite3 *db, t_get_contacts contact);
int mx_cache_chat(sqlite3 *db, t_get_chats chat);
t_list *mx_get_cached_chats(sqlite3 *db);
t_list *mx_get_cached_contacts(sqlite3 *db);
t_list *mx_get_cached_messages(sqlite3 *db);
t_get_settings *mx_get_cached_settings(sqlite3 *db);
int mx_update_settings_email(sqlite3 *db, char *new_email, char *old_email);
int mx_delete_cached_message(sqlite3 *db, int message_id);
int mx_delete_cached_contact(sqlite3 *db, char *username);
int mx_delete_cached_chat(sqlite3 *db, int chat_id);
t_list *mx_get_cached_messages(sqlite3 *db, int chat_id);

#endif //DATA_CACHING_H
