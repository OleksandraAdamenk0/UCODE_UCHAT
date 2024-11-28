//
// Created by oleksandra on 22/11/24.
//

#include "server.h"
#include "database_managment.h"

void *mx_get_db() {
    if (db) return (void *)db;
    else return NULL;
}
