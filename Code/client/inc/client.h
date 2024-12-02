//
// Created by oleksandra on 17/11/24.
//

#ifndef UCODE_UCHAT_MAIN_CLIENT_H
#define UCODE_UCHAT_MAIN_CLIENT_H

#include "libmx.h"
#include "logger.h"
#include "responses.h"

extern int mode;
extern long long int id;

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

int mx_send_data(char *data);
int mx_receive_data(char **response);

// GUI SECTION
int mx_run_app(int argc, const char *argv[]);

// DATA EXCHANGE SECTION
int mx_handle_request(char *data, t_action action, t_response **response);

#endif //UCODE_UCHAT_MAIN_CLIENT_H
