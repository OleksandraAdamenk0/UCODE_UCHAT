//
// Created by oleksandra on 21/11/24.
//

#include "gui.h"

GtkWidget *window;

int mx_create_window() {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), APP_NAME);
    gtk_window_set_default_size(GTK_WINDOW(window), WIDTH, HEIGHT);
}
