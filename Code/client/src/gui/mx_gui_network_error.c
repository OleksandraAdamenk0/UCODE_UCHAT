//
// Created by oleksandra on 21/11/24.
//

#include "client.h"
#include "gui.h"

int mx_gui_network_error() {
    mx_create_window();
    WebKitWebView *web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());
    const char *html_content = mx_file_to_str(NETWORK_ERROR_HTML)
    webkit_web_view_load_html(web_view, html_content, NULL);
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(web_view));
    gtk_widget_show_all(window);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_main();
    return 0;
}
