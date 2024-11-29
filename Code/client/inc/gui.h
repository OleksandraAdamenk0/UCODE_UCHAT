//
// Created by oleksandra on 21/11/24.
//

#ifndef UCODE_UCHAT_MAIN_GRAPHICAL_INTERFACE_H
#define UCODE_UCHAT_MAIN_GRAPHICAL_INTERFACE_H

#include <gtk/gtk.h>
#include <glib.h>
#include <webkit2/webkit2.h>

#define WIDTH 800
#define HEIGHT 600

#define APP_NAME "TAZIK"

#define RSC "/client/rsc"
#define HTML RSC "/html"
#define REGISTRATION_HTML HTML "/registration.html"
#define LOGIN_HTML HTML "/login.html"
#define NETWORK_ERROR_HTML HTML "/network_error.html"

extern GtkApplication *app;
extern GtkWidget *window;
extern WebKitWebView *webview;
extern WebKitUserContentManager *manager;

// UTILS
char *mx_get_cur_dir();

void mx_gui_init(GtkApplication *app, gpointer user_data);

// PAGES
int mx_load_registration_page();
int mx_load_login_page();

#endif //UCODE_UCHAT_MAIN_GRAPHICAL_INTERFACE_H
