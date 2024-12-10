//
// Created by oleksandra on 21/11/24.
//

#ifndef UCODE_UCHAT_MAIN_RESPONSES_H
#define UCODE_UCHAT_MAIN_RESPONSES_H

#include <time.h>

typedef struct s_registration_response {
    char *tokens[2];
} t_registration_response;

typedef struct s_login_response {
    char *tokens[2];
} t_login_response;

typedef struct s_chat {
    int id;
    char *name;
    // photo in the future
} t_chat;

typedef struct s_chats {
    int count;
    t_chat *chats;
} t_chats;

typedef struct s_chats_response {
    char *tokens[2];
} t_chats_response;

typedef struct s_message {
    int id;
    int chat_id;
    int sender_id;
    int reply_to_id;
    time_t timestamp;
    void *binary;
    int binary_size;
    char *message;
} t_message;

typedef enum e_action {
    REGISTRATION,
    LOGIN,
    GET_CONTACTS,
    GET_CHATS,
    GET_LAST_MSG
} t_action;

typedef struct s_response {
    t_action action;
    int status;
    char *msg;
    void *data;
} t_response;

#endif //UCODE_UCHAT_MAIN_RESPONSES_H
