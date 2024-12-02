//
// Created by oleksandra on 21/11/24.
//

#ifndef UCODE_UCHAT_MAIN_RESPONSES_H
#define UCODE_UCHAT_MAIN_RESPONSES_H

typedef struct {
    char *tokens[2];
} t_registration_response;

typedef struct {
    char *tokens[2];
} t_login_response;

typedef enum {
    REGISTRATION,
    LOGIN,
    GET_CONTACTS,
    GET_CHATS
} t_action;

typedef struct {
    t_action action;
    int status;
    char *msg;
    void *data;
} t_response;

#endif //UCODE_UCHAT_MAIN_RESPONSES_H
