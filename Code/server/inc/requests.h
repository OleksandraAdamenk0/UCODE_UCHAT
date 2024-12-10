//
// Created by oleksandra on 22/11/24.
//

#ifndef UCODE_UCHAT_MAIN_REQUEST_H
#define UCODE_UCHAT_MAIN_REQUEST_H

#include <time.h>

#define UNIQUE_USERNAME "UNIQUE constraint failed: users.username"
#define UNIQUE_PHONE "UNIQUE constraint failed: users.phone"
#define UNIQUE_EMAIL "UNIQUE constraint failed: users.email"

typedef struct {
    char *username;
    char *password;
    char *email;
    char *phone;
    char *photo;
    long long int photo_size; // not sure that its needed
} t_registration;

typedef struct {
    char *username;
    char *password;
} t_login;

typedef struct {
    char chat_id; 
    char user_id; 
} t_add_user_chat;

typedef struct {
    char chat_id; 
    char *chat_name;
    char *photo;
   // t_add_user_chat user;
} t_chat_req;

typedef struct {
    char message_id;
    char chat_id;
    time_t timestamp;
    char send_to_id;
    char send_from_id;
    char *message;
    char *binary;
} t_add_message, t_del_message;

typedef struct {
    char user_id;
    char *username;
} t_get_settings;

typedef struct {
    char user_id;
    char theme;
    char email;
    char phone; 
    char photo;
} t_add_settings;

typedef struct {
    char *username;
    char *photo;
} t_get_contacts;

#endif //UCODE_UCHAT_MAIN_REQUEST_H
