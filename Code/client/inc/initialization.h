//
// Created by oleksandra on 17/11/24.
//

#ifndef CLIENT_INITIALIZATION_H
#define CLIENT_INITIALIZATION_H

#define LOGGER_CONFIG "client/logger.conf"

int mx_parse_args(int argc, const char *argv[], int *port, char **ip);
int mx_init_gtk();

#endif //CLIENT_INITIALIZATION_H
