//
// Created by oleksandra on 17/11/24.
//

#ifndef UCODE_UCHAT_MAIN_CLIENT_H
#define UCODE_UCHAT_MAIN_CLIENT_H

#include "libmx.h"
#include "logger.h"
#include "cJSON.h"
#include <stdlib.h>

extern int mode;

typedef enum {
    REGISTRATION,
    LOGIN,
    GET_CONTACTS,
    GET_CHATS
} t_api_type;

typedef struct {
    t_api_type action;
    void *data;
} t_request;

typedef struct {
    t_api_type action;
    int status;
    char *msg;
    void *data;
} t_response;

// INIT SECTION
int mx_init(int argc, const char *argv[]);
int mx_create_app(char *window);
int mx_db_init();
void mx_db_finalize();

// DATABASE SECTION
bool mx_isdb_valid();

// CONNECTION SECTION
void *mx_connection_thread(void *arg);
void mx_close_connection();

int mx_send_data(int fd, char *data);
int mx_receive_data(int fd, char **response);

// GUI SECTION
int mx_run_app(int argc, const char *argv[]);

// DATA EXCHANGE SECTION
char *mx_create_request(t_request *data);

#endif //UCODE_UCHAT_MAIN_CLIENT_H
