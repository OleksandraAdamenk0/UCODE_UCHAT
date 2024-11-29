#include "gui.h"
#include "logger.h"

static void clear_handlers() {
    webkit_user_content_manager_unregister_script_message_handler(manager, "submitForm");
    webkit_user_content_manager_unregister_script_message_handler(manager, "goToLogin");
    logger_debug("All handlers cleared.\n");
}

static void handle_submit(WebKitUserContentManager *manager,
                          WebKitJavascriptResult *js_result,
                          gpointer user_data) {
    logger_info("Registration form submitted\n");
    JSCValue *value = webkit_javascript_result_get_js_value(js_result);
    if (jsc_value_is_string(value)) {
        gchar *json_data = jsc_value_to_string(value);
        logger_debug("Received JSON for registration\n");

        // Здесь можно обработать JSON-строку
        g_free(json_data);
        clear_handlers();
//        load_chat_page();
    } else logger_debug("Error: Expected a JSON string from JavaScript!\n");
}

static void goToLogin(WebKitUserContentManager *manager,
                      WebKitJavascriptResult *js_result,
                      gpointer user_data) {
    logger_info("Login link pressed\n");
    // Здесь можно обработать JSON-строку
    clear_handlers();
    mx_load_login_page();
}

static void set_handlers() {
    webkit_user_content_manager_register_script_message_handler(manager, "submitForm");
    g_signal_connect(manager, "script-message-received::submitForm", G_CALLBACK(handle_submit), NULL);

    webkit_user_content_manager_register_script_message_handler(manager, "goToLogin");
    g_signal_connect(manager, "script-message-received::goToLogin", G_CALLBACK(goToLogin), NULL);

    logger_debug("Handlers set for registration page.\n");
}

int mx_load_registration_page() {
    logger_info("Loading registration page\n");
    if (!window) {
        logger_fatal("Application window was not created"
                     " before trying to show screen\n");
        return -1;
    }

    char *path1 = mx_get_cur_dir();
    char *path = mx_strjoin(path1, REGISTRATION_HTML);

    set_handlers();
    webkit_web_view_load_uri(webview, path);

    free(path);
    free(path1);
    return 0;
}

