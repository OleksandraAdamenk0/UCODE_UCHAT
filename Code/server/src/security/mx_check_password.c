//
// Created by oleksandra on 09/12/24.
//

#include "security.h"
#include "database.h"
#include "logger.h"
#include "libmx.h"

int mx_check_password(long long int id, char *password) {
    char *db_password = mx_get_password(id);
    if (!db_password) return -2;
    // some decription here
    logger_debug(db_password);
    logger_debug(password);
    if (mx_strcmp(db_password, password) != 0) return -1;
    return 0;
}
