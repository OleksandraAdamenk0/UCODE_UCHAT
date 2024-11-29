//
// Created by oleksandra on 21/11/24.
//

#include "gui.h"
#include "logger.h"

GtkWidget *window;
WebKitWebView *webview;
WebKitUserContentManager *manager;

static int init_webview() {
    webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
    if (webview == NULL) return -1;

    WebKitSettings *settings = webkit_web_view_get_settings(webview);
    if (settings == NULL) return -2;
    webkit_settings_set_enable_javascript(settings, TRUE);

    manager = webkit_web_view_get_user_content_manager(webview);
    if (manager == NULL) return -1;

    return 0;
}

static int init_gtk() {
    if (gtk_init_check(NULL, NULL) == FALSE) {
        logger_fatal("Failed to initialize GUI.\n");
        logger_debug("Failed to initialize GTK.\n");
        return -1;
    } else logger_debug("GTK initialized\n");
    return 0;
}

static int init_window() {
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    if (!window) {
        logger_debug("Failed to create the window.\n");
        return -1;
    }
    logger_debug("Window created\n");
    gtk_window_set_title(GTK_WINDOW(window), APP_NAME);
    gtk_window_set_default_size(GTK_WINDOW(window), WIDTH, HEIGHT);

    if (!g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL)) {
        logger_debug("Failed to connect the destroy signal.\n");
        return -1;
    }
    logger_debug("Destroy signal connected\n");
    return 0;
}

void mx_gui_init(GtkApplication *app, gpointer user_data) {
    logger_info("Gui initialization\n");

    if (init_gtk() < 0) {
        logger_fatal("Failed to initialize GUI.\n");
        return;
    }
    if (init_webview() < 0) {
        logger_fatal("Failed to initialize GUI.\n");
        return;
    }
    if (init_window() < 0) {
        logger_fatal("Failed to initialize GUI.\n");
        return;
    }
    if (mx_load_load_page() < 0) {
        logger_fatal("Failed to load load page\n");
        return;
    }
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(webview));
    gtk_widget_show_all(window);
    gtk_main();
}
