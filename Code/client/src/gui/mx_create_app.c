//
// Created by oleksandra on 29/11/24.
//

#include "client.h"
#include "gui.h"

GtkApplication *app;

static int on_command_line(GApplication *app, GApplicationCommandLine *cmdline,
                           gpointer user_data) {
    int argc;
    char **argv = g_application_command_line_get_arguments(cmdline, &argc);
    logger_debug("Command line args handeled by GTK\n");
    return 0;
}


int mx_create_app(char *window) {
    app = gtk_application_new("com.campus.uchat", G_APPLICATION_HANDLES_COMMAND_LINE);
    if (app == NULL) {
        logger_fatal("Failed to create GTK app\n");
        return -1;
    }

    char *data = mx_strdup(window);
    printf("data: %s\n", data);
    g_signal_connect(app, "activate", G_CALLBACK(mx_gui_init), (gpointer)data);
    g_signal_connect(app, "command-line", G_CALLBACK(mx_gui_init), (gpointer)data);
    return 0;
}
