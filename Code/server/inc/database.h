#ifndef SERVER_DATABASE_H
#define SERVER_DATABASE_H

#include "sqlite3.h"
#include "requests.h"
#include "libmx.h"

#define DB_DIR "server/db"
#define SCRIPTS DB_DIR "/scripts"
#define INIT_SCRIPT SCRIPTS "/init.sql"
#define DB_NAME DB_DIR "/server.db"

extern sqlite3 *db;

typedef enum e_users_fields {
    USERNAME, PASSWORD, EMAIL, PHONE, PHOTO
} t_users_field;

int mx_register_user(t_registration *data);
int mx_get_user_id(const char *value, t_users_field field);
char *mx_get_password(int id);

t_list *mx_get_all_chats(int id);


#endif //SERVER_DATABASE_H
