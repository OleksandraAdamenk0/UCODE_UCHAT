//
// Created by oleksandra on 21/11/24.
//

#include "client.h"
#include "gui.h"

int mx_gui_init(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    mx_create_window();
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_main();
    return 0;
}
