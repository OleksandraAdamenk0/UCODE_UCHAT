//
// Created by oleksandra on 03/12/24.
//

#include "client.h"

int main(int argc, const char *argv[]) {
    if (mx_init(argc, argv) < 0) return -1;
    int status = mx_run_app(argc, (char **)argv);
    mx_close_app();
    return status;
}
