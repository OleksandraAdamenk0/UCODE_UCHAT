//
// Created by aleksa on 11/2/24.
//
#include "initialization.h"

int mx_create_daemon() {
	pid_t pid = fork();

    if (pid < 0) return -1;  // error
    if (pid > 0) exit(EXIT_SUCCESS);  // parrrent process

    // creation of the new session to unbind daemon from the terminal
    // (f. ex if terminal is closed, daemon will not terminate)
    if (setsid() < 0) return -1;

	// Second fork to ensure the child process will not regain control
    // of a terminal
    pid = fork();
    if (pid < 0) return -1;
    if (pid > 0) exit(EXIT_SUCCESS);

    umask(0);  // full read, write, and execute permissions
    // chdir("/");  // can compete with file writing

    // print pid
    int daemon_pid = getpid();
    mx_printint(daemon_pid);
    mx_printchar('\n');

    // close standart outputs
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    return 0;
}
