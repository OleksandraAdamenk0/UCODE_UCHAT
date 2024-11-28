//
// Created by oleksandra on 21/11/24.
//

#include "client.h"
#include "gui.h"

int mx_gui_init(int argc, char *argv[]) {
    if (gtk_init_check(&argc, &argv) == FALSE) {
        logger_fatal("Failed to initialize GUI.\n");
        logger_debug("Failed to initialize GTK.\n");
        return -1;
    } else logger_debug("GTK initialized\n");
    if (mx_create_window() < 0) {
        logger_fatal("Failed to initialize GUI.\n");
        logger_debug("Failed to create the window.\n");
        return -1;
    } else logger_debug("Window created\n");
    if (!g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL)) {
        logger_fatal("Failed to initialize GUI.\n");
        logger_debug("Failed to connect the destroy signal.\n");
        return -1;
    } else logger_debug("Destroy signal connected\n");
    return 0;
}
