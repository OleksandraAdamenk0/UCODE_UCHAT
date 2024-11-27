#include "client.h"
#include "gui.h"

int mx_gui_network_error() {
    // if (window == NULL) mx_create_window();
    if (!window) {
        logger_fatal("application window was not created"
                     " before trying to show screen\n");
        return -1;
    }

    char *path1 = mx_get_cur_dir();
    char *path = mx_strjoin(path1, LOGIN_HTML);
    free(path1);

    WebKitWebView *webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
    webkit_web_view_load_uri(webview, path);

    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(webview));
    gtk_widget_show_all(window);
    return 0;
}
