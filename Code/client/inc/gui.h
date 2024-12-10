//
// Created by oleksandra on 21/11/24.
//

#ifndef CLIENT_GUI_H
#define CLIENT_GUI_H

#include <gtk/gtk.h>
#include <glib.h>
#include <webkit2/webkit2.h>

#define WIDTH 800
#define HEIGHT 600
#define APP_NAME "TAZIK"

extern GtkApplication *app;
extern GtkWidget *window;
extern WebKitWebView *webview;
extern WebKitUserContentManager *manager;

#define RSC "/client/rsc"

// HTML
#define HTML RSC "/html"
#define LOAD_HTML HTML "/load.html"
#define LOGIN_HTML HTML "/login.html"
#define ERROR_HTML HTML "/error.html"
#define REGISTRATION_HTML HTML "/registration.html"
#define CHATS_HTML HTML "/chats.html"


typedef int (*set_handlers_ptr)();

typedef enum e_pages {
    LOAD_PAGE, LOGIN_PAGE, ERROR_PAGE, CHATS_PAGE, REGISTRATION_PAGE
} t_pages;

void mx_init_gui(GtkApplication *app, gpointer user_data);

int mx_load_page(t_pages page);
int mx_load_handlers();
int mx_login_handlers();
int mx_error_handlers();
int mx_registration_handlers();
int mx_chats_handlers();

#endif //CLIENT_GUI_H
