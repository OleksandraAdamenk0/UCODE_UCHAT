//
// Created by oleksandra on 17/11/24.
//

#include "client.h"
#include "connection.h"

void mx_close_connection() {
    close(fd);
    logger_info("connection closed\n");
}
