//
// Created by oleksandra on 29/11/24.
//

#include "gui.h"
#include "client.h"
#include "logger.h"
#include "connection.h"
#include "utils.h"

static void connect_to_server(WebKitUserContentManager *manager,
                    WebKitJavascriptResult *js_result,
                    gpointer user_data);

static void choose_mode(WebKitUserContentManager *manager,
                        WebKitJavascriptResult *js_result,
                        gpointer user_data);

//static void go_to_login(WebKitUserContentManager *manager,
//                        WebKitJavascriptResult *js_result,
//                        gpointer user_data);
//
//static void go_to_error(WebKitUserContentManager *manager,
//                        WebKitJavascriptResult *js_result,
//                        gpointer user_data);

int mx_load_handlers() {
    if (!webkit_user_content_manager_register_script_message_handler(manager, "connectToServer")){
        logger_error("set_handlers: Failed to register 'connectToServer' handler");
        return -1;
    }
    if (g_signal_connect(manager, "script-message-received::connectToServer", G_CALLBACK(connect_to_server), NULL) == 0) {
        logger_error("set_handlers: Failed to connect 'connect_to_server' signal");
        return -1;
    }
    if (!webkit_user_content_manager_register_script_message_handler(manager, "chooseMode")) {
        logger_error("set_handlers: Failed to register 'chooseMode' handler");
        return -1;
    }
    if (g_signal_connect(manager, "script-message-received::chooseMode", G_CALLBACK(choose_mode), NULL) == 0) {
        logger_error("set_handlers: Failed to connect 'chooseMode' signal");
        return -1;
    }
//    if (!webkit_user_content_manager_register_script_message_handler(manager, "goToError")) {
//        logger_error("set_handlers: Failed to register 'goToError' handler");
//        return -1;
//    }
//    if (g_signal_connect(manager, "script-message-received::goToError", G_CALLBACK(go_to_error), NULL) == 0) {
//        logger_error("set_handlers: Failed to connect 'goToError' signal");
//        return -1;
//    }
    logger_debug("mx_load_load_page: Handlers set for the page");
    return 0;
}

static void clear_handlers() {
    webkit_user_content_manager_unregister_script_message_handler(manager, "connect");
    logger_debug("All handlers cleared.\n");
}

static void connect_to_server(WebKitUserContentManager *manager,
                    WebKitJavascriptResult *js_result,
                    gpointer user_data) {
    logger_debug("connect_to_server: The function entered");
    pthread_t conn_thread;
    pthread_create(&conn_thread, NULL, mx_connection_thread, NULL);
    pthread_detach(conn_thread);
    logger_debug("connect_to_server: The function created");
}

static void choose_mode(WebKitUserContentManager *manager,
                        WebKitJavascriptResult *js_result,
                        gpointer user_data) {
    clear_handlers();
    if (mode == -2) mx_load_page(ERROR_PAGE);
    else mx_load_page(LOGIN_PAGE);
}

//static void go_to_login(WebKitUserContentManager *manager,
//                        WebKitJavascriptResult *js_result,
//                        gpointer user_data) {
//    clear_handlers();
//    mx_load_page(LOGIN_PAGE);
//}
//
//static void go_to_error(WebKitUserContentManager *manager,
//                        WebKitJavascriptResult *js_result,
//                        gpointer user_data) {
//    clear_handlers();
//    mx_load_page(ERROR_PAGE);
//}
