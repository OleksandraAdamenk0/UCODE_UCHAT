//
// Created by oleksandra on 21/11/24.
//

#include "gui.h"
#include "logger.h"

GtkWidget *window;
WebKitWebView *webview;
WebKitUserContentManager *manager;

static int init_webview() {
    // create webview
    webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
    if (webview == NULL) return -1;

    // set up
    WebKitSettings *settings = webkit_web_view_get_settings(webview);
    if (settings == NULL) return -1;
    webkit_settings_set_enable_developer_extras(settings, TRUE);
    webkit_settings_set_enable_javascript(settings, TRUE);
    g_object_set(settings, "enable-page-cache", FALSE, NULL);

    // create manager
    manager = webkit_web_view_get_user_content_manager(webview);
    if (manager == NULL) return -1;

    return 0;
}

static int init_window() {
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    if (!window) return -1;

    // set up
    gtk_window_set_title(GTK_WINDOW(window), APP_NAME);
    gtk_window_set_default_size(GTK_WINDOW(window), WIDTH, HEIGHT);

    // connect destroy signal
    if (!g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL))
        return -1;

    return 0;
}

void mx_init_gui(GtkApplication *app, gpointer user_data) {
    // check if gtk library was initialized
    if (gtk_init_check(NULL, NULL) == FALSE) {
        logger_fatal("mx_init_gui: Failed to initialize GUI.");
        logger_debug("mx_init_gui: GTK was not initialized");
        return;
    }
    logger_debug("mx_init_gui: GTK was initialized");

    // init webview
    if (init_webview() < 0) {
        logger_fatal("mx_init_gui: Failed to initialize GUI.");
        logger_debug("mx_init_gui: Failed to initialize webview");
        return;
    }
    logger_debug("mx_init_gui: webview was initialized");

    // init window
    if (init_window() < 0) {
        logger_fatal("mx_init_gui: Failed to initialize GUI.");
        logger_debug("mx_init_gui: Failed to initialize window");
        return;
    }
    logger_debug("mx_init_gui: window was initialized");

    // load starting page
    if (mx_load_page(LOAD_PAGE) < 0) {
        logger_fatal("mx_init_gui: Failed to initialize GUI.");
        logger_debug("mx_init_gui: Failed to load starting page");
        return;
    }
    logger_debug("mx_init_gui: init page was initialized");

    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(webview));
    gtk_widget_show_all(window);
    logger_info("mx_init_gui: Going to the gtk_main()");
    gtk_main();
}
