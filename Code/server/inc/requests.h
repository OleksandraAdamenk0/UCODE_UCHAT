//
// Created by oleksandra on 22/11/24.
//

#ifndef UCODE_UCHAT_MAIN_REQUEST_H
#define UCODE_UCHAT_MAIN_REQUEST_H

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

#endif //UCODE_UCHAT_MAIN_REQUEST_H
