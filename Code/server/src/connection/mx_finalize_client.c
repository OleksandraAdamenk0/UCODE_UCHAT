//
// Created by oleksandra on 28/11/24.
//

#include "connection.h"

void mx_finalize_client(t_client_info *info) {
    if (info) {
        if (info->fd) {
            close(*(info->fd));
            free(info->fd);
        }
        free(info);
    }
}
