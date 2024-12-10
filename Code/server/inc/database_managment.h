#ifndef DATABASE_MANAGMENT_H
#define DATABASE_MANAGMENT_H

#include "sqlite3.h"
#include "cJSON.h"
#include "libmx.h"
#include "requests.h"

#include <stdio.h>

#define DB_DIR "server/db"
#define SCRIPTS DB_DIR "/scripts"
#define INIT_SCRIPT SCRIPTS "/init.sql"
#define DB_NAME DB_DIR "/server.db"

extern sqlite3 *db;

int mx_create_dir();
//int mx_init_tables();

int mx_register_user(t_registration *data);
int mx_get_user_id_by_username(const char *username);

// DATABASE
int mx_db_init();
void mx_db_finalize();
    //delite data 

int mx_delete_chat(sqlite3 *db, int chat_id);
int delete_message(sqlite3 *db, t_del_message *msg);
int mx_delete_user(sqlite3 *db, char *user_id);

    //get data 
t_list *mx_get_all_chats(sqlite3 *db); 
t_list *get_all_contacts(sqlite3 *db);
void *mx_get_db();
int return_settings(sqlite3 *db, t_get_settings *user, t_add_settings *settings);
int mx_get_user_id_by_username(const char *username);

    //registration 
int mx_register_user(t_registration *data);

    //save 
int mx_save_contact(sqlite3 *db, t_get_contacts contact);
int save_message(sqlite3 *db, t_add_message *new_message);
int save_new_chat(sqlite3 *db, t_chat_req *chat_data);
int save_settings(sqlite3 *db, t_add_settings *user_settings);
int add_user_to_chat(sqlite3 *db, t_add_user_chat *chat_user_data);

    //update
int mx_update_settings_theme(sqlite3 *db, char *new_theme, char *old_theme);
int mx_update_photo(sqlite3 *db, const char *table_name, const char *condition_column,
                    const char *new_photo, int new_photo_size, 
                    const char *condition_value, int condition_size);
//utils 
int is_data_in_table(sqlite3 *db, const char *table_name, const char *column_name, const char *value);
#endif
