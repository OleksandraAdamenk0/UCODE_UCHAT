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
int mx_get_user_id(t_login *data, char **user_id);

#endif
