//
// Created by oleksandra on 09/12/24.
//

#ifndef SERVER_RESPONSES_H
#define SERVER_RESPONSES_H

typedef struct s_chat {
    int id;
    char *name;
    // photo in the future
} t_chat;

typedef struct s_chats {
    int count;
    t_chat *chats;
} t_chats;

#endif //SERVER_RESPONSES_H
