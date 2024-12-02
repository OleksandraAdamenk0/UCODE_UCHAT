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

typedef enum e_users_fields {
    USERNAME, PASSWORD, EMAIL, PHONE, PHOTO
} t_users_field;

extern sqlite3 *db;

int mx_create_dir();
//int mx_init_tables();

int mx_register_user(t_registration *data);
int mx_get_user_id(const char *value, t_users_field field);
#endif
