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

#endif //DATA_CACHING_H
