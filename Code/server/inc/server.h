//
// Created by aleksa on 11/2/24.
//

#ifndef SERVER_H
#define SERVER_H

#include <stdlib.h>
#include <netinet/in.h>

#include "libmx.h"
#include "logger.h"
#include "connection.h"

extern int port;
extern char *ip;

// INITIALIZATION
int mx_init_server(int argc, const char * argv[]);
void mx_finalize_server();
//void *mx_handle_client(void *client_socket);

// REQUESTS
char *mx_handle_request(const char *request_str);

// CONNECTIONS
int mx_open_connection();
int mx_accept_connections();

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
#endif //SERVER_H
