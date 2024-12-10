#ifndef CLIENT_DATABASE_H
#define CLIENT_DATABASE_H

#include <sqlite3.h>

#define DB_DIR "client/db"
#define SCRIPTS DB_DIR "/scripts"
#define INIT_SCRIPT SCRIPTS "/update.sql"
#define DB_NAME DB_DIR "/app.db"

extern sqlite3 *db;

int mx_init_db();
int mx_is_db_valid();

int mx_update_db();
int mx_update_chats();
int mx_create_tables();

#endif //CLIENT_DATABASE_H
