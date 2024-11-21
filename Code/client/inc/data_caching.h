#ifndef DATA_CACHING_H
#define DATA_CACHING_H

#include <sqlite3.h>
#include <stdio.h>
#include <stdbool.h>

void mx_create_client_tables(sqlite3 *db);
bool mx_is_database_valid(const char *db_path);

#endif //DATA_CACHING_H
