//
// Created by oleksandra on 03/12/24.
//

#include "initialization.h"
#include "logger.h"
#include "gui.h"

GtkApplication *app;

int mx_init_gtk(){
    app = gtk_application_new("com.campus.uchat", G_APPLICATION_HANDLES_COMMAND_LINE);
    if (app == NULL) {
        logger_fatal("mx_init_gtk: Failed to create GTK app");
        return -1;
    }
    g_signal_connect(app, "activate", G_CALLBACK(mx_init_gui), NULL);
    g_signal_connect(app, "command-line", G_CALLBACK(mx_init_gui), NULL);
    logger_info("mx_init_gtk: success");
    return 0;
}
