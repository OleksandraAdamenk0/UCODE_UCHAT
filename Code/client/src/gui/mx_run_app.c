//
// Created by oleksandra on 29/11/24.
//

#include "client.h"
#include "gui.h"

int mx_run_app(int argc, const char *argv[]) {
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    char *msg = "App ended with status ";
    char *msg1 = mx_strjoin(msg, mx_itoa(status));
    msg = mx_strjoin(msg1, "\n");
    logger_info(msg);
    free(msg);
    free(msg1);
    return status;
}
