//
// Created by oleksandra on 29/11/24.
//

#include "gui.h"
#include "client.h"

static void clear_handlers() {
    webkit_user_content_manager_unregister_script_message_handler(manager, "connect");
    logger_debug("All handlers cleared.\n");
}

static void connect(WebKitUserContentManager *manager,
                          WebKitJavascriptResult *js_result,
                          gpointer user_data) {
    pthread_t conn_thread;
    pthread_create(&conn_thread, NULL, mx_connection_thread, NULL);
    pthread_detach(conn_thread);
}

static void go_to_login(WebKitUserContentManager *manager,
                    WebKitJavascriptResult *js_result,
                    gpointer user_data) {
    clear_handlers();
    mx_load_login_page();
}

static void go_to_error(WebKitUserContentManager *manager,
                        WebKitJavascriptResult *js_result,
                        gpointer user_data) {
    clear_handlers();
    mx_load_error_page();
}

static void set_handlers() {
    webkit_user_content_manager_register_script_message_handler(manager, "connect");
    g_signal_connect(manager, "script-message-received::connect", G_CALLBACK(connect), NULL);
    webkit_user_content_manager_register_script_message_handler(manager, "goToLogin");
    g_signal_connect(manager, "script-message-received::goToLogin", G_CALLBACK(go_to_login), NULL);
    webkit_user_content_manager_register_script_message_handler(manager, "goToError");
    g_signal_connect(manager, "script-message-received::goToError", G_CALLBACK(go_to_error), NULL);
    logger_debug("Handlers set for load page.\n");
}

int mx_load_load_page() {
    logger_info("Loading login page\n");
    if (!window) {
        logger_fatal("Application window was not created"
                     " before trying to show screen\n");
        return -1;
    }

    char *path1 = mx_get_cur_dir();
    char *path = mx_strjoin(path1, LOAD_HTML);

    set_handlers();
    webkit_web_view_load_uri(webview, path);

    free(path);
    free(path1);
    return 0;
}
