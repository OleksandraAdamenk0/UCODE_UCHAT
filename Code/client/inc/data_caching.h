#ifndef CLIENT_DATABASE_H
#define CLIENT_DATABASE_H

#include <sqlite3.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>

#define DB_DIR "client/db"
#define SCRIPTS DB_DIR "/scripts"
#define INIT_SCRIPT SCRIPTS "/update.sql"
#define DB_NAME DB_DIR "/app.db"

extern sqlite3 *db;

void mx_create_client_tables(sqlite3 *db);

int mx_update_db();
int mx_update_chats();
int mx_update_contacts();
int mx_create_tables();

#endif //CLIENT_DATABASE_H
