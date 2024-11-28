#ifndef DATABASE_MANAGMENT_H
#define DATABASE_MANAGMENT_H

#include "sqlite3.h"
#include "cJSON.h"
#include <stdio.h>
#include "libmx.h"
#include "cdecode.h"
#include "cencode.h"
#include "logger.h"

typedef struct {
    char *username;
    char *password;
    char *phone;
    char *email;
    char *photo;
}       t_get_user;

void mx_create_server_tables(sqlite3 *db);
int mx_register_user(sqlite3 *db, const cJSON *request);

#endif
