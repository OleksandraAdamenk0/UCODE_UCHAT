//
// Created by oleksandra on 04/12/24.
//

#ifndef CLIENT_UTILS_H
#define CLIENT_UTILS_H

char *mx_sprintf(const char *format, ...);
char *mx_curdir();

int mx_base64_encode(const char *input_str, char **encoded_str);
int mx_base64_decode(const char *encoded_str, char **decoded_str);

#endif //CLIENT_UTILS_H
