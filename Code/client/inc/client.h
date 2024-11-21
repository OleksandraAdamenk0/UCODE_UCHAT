//
// Created by oleksandra on 17/11/24.
//

#ifndef UCODE_UCHAT_MAIN_CLIENT_H
#define UCODE_UCHAT_MAIN_CLIENT_H

#include "libmx.h"
#include "logger.h"

extern int port;
extern char *ip;

extern bool online_mode;

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
int mx_init(int argc, char *argv[]);
int mx_gui_init(int argc, char *argv[]);

// CONNECTION SECTION
int mx_open_connection();
void mx_close_connection(int sockfd);
void debug_send(int fd, char *str);

// GUI SECTION
int mx_gui_network_error();

// DATA EXCHANGE SECTION
char *mx_create_request(t_request *data);

#endif //UCODE_UCHAT_MAIN_CLIENT_H
