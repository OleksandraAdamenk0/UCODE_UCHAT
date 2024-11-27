//
// Created by oleksandra on 21/11/24.
//

#ifndef UCODE_UCHAT_MAIN_GRAPHICAL_INTERFACE_H
#define UCODE_UCHAT_MAIN_GRAPHICAL_INTERFACE_H

#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

#define WIDTH 1440
#define HEIGHT 1024

#define APP_NAME "TAZIK"

#define RSC "/client/rsc"
#define HTML RSC "/html"
#define REGISTRATION_HTML HTML "/registration.html"
#define LOGIN_HTML HTML "/login.html"
#define NETWORK_ERROR_HTML HTML "/network_error.html"

extern GtkWidget *window;

int mx_create_window();

#endif //UCODE_UCHAT_MAIN_GRAPHICAL_INTERFACE_H
