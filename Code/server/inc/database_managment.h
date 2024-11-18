#ifndef DATABASE_MANAGMENT_H
#define DATABASE_MANAGMENT_H

#include <sqlite3.h>
#include <cjson/cJSON.h>
#include <stdio.h>

void mx_create_tables(sqlite3 *db);

#endif
