#pragma once

#include "../libmx/inc/libmx.h"
#include <stdio.h>
#include <sqlite3.h>

void insert_data(sqlite3 *db);
int print_callback(void *not_used, int argc, char **argv, char **col_name);
int print_query_results(sqlite3 *db, const char *sql);
int execute_sql(sqlite3 *db, const char *sql);
//void mx_printerr(const char* errortext);
