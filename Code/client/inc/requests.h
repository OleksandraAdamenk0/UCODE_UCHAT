//
// Created by oleksandra on 21/11/24.
//

#ifndef UCODE_UCHAT_MAIN_REQUESTS_H
#define UCODE_UCHAT_MAIN_REQUESTS_H

typedef struct {
    char *action;
    char *username;
    char *password;
    char *email;
    char *phone;
} t_registration_request;

typedef struct {
    char *action;
    char *username;
    char *password;
} t_login_request;

typedef struct {
    char *action;
    char *username;
} t_get_contacts_request;

typedef struct {
    char *action;
    char *username;
} t_get_chats_request;

#endif //UCODE_UCHAT_MAIN_REQUESTS_H
