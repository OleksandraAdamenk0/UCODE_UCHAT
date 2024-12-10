//
// Created by oleksandra on 29/11/24.
//

#include "client.h"
#include "logger.h"
#include "utils.h"
#include "gui.h"

int mx_run_app(int argc, char *argv[]) {
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    char *msg = mx_sprintf("mx_run_app: App ended with status %d", status);
    logger_info(msg);
    mx_strdel(&msg);
    return status;
}
