//
// Created by oleksandra on 17/11/24.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

extern int mode;
extern long long int id;

int mx_init(int argc, const char *argv[]);
int mx_run_app(int argc, char *argv[]);
int mx_close_app();

#endif //CLIENT_CLIENT_H
