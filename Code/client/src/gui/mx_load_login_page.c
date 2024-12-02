#include "client.h"
#include "gui.h"

static void clear_handlers() {
    webkit_user_content_manager_unregister_script_message_handler(manager, "submitForm");
    webkit_user_content_manager_unregister_script_message_handler(manager, "goToRegister");
    logger_debug("All handlers cleared.\n");
}

static void handle_submit(WebKitUserContentManager *manager,
                          WebKitJavascriptResult *js_result,
                          gpointer user_data) {
    logger_info("Login form submitted\n");
    JSCValue *value = webkit_javascript_result_get_js_value(js_result);
    if (!jsc_value_is_string(value)) {
        logger_debug("Error: Expected a JSON string from JavaScript!\n");
        clear_handlers();
        mx_load_error_page();
        return;
    }
    gchar *json_data = jsc_value_to_string(value);
    logger_debug("Received JSON for login\n");

    t_response *response = malloc(sizeof(t_response));
    int status = mx_handle_request((char *)json_data, LOGIN, &response);
    g_free(json_data);

    if (!response) {
        logger_error("Response from server is empty\n");
        clear_handlers();
        mx_load_error_page();
        return;
    }
    logger_info(response->msg);
    if (response->status == 0) {
        t_login_response *data = response->data;
        id = mx_atoi(data->tokens[0]);
        free(data);
        free(response);
        clear_handlers();
        mx_load_chat_page();
        return;
    } else if (response->status <= -2) {
        clear_handlers();
        free(response);
        mx_load_error_page();
        return;
    }
    char *cmd;
    if (response->status == -1) {
        cmd = mx_create_js_func_call("invalidData", response->msg);
    }
    webkit_web_view_run_javascript(webview, cmd, NULL, NULL, NULL);
    free(response);
    free(cmd);
    return;
}

static void goToRegister(WebKitUserContentManager *manager,
                          WebKitJavascriptResult *js_result,
                          gpointer user_data) {
    logger_info("Register link pressed\n");
    clear_handlers();
    mx_load_registration_page();
}

static void set_handlers() {
    webkit_user_content_manager_register_script_message_handler(manager, "submitLoginForm");
    g_signal_connect(manager, "script-message-received::submitLoginForm", G_CALLBACK(handle_submit), NULL);

    webkit_user_content_manager_register_script_message_handler(manager, "goToRegister");
    g_signal_connect(manager, "script-message-received::goToRegister", G_CALLBACK(goToRegister), NULL);

    logger_debug("Handlers set for login page.\n");
}

int mx_load_login_page() {
    logger_info("Loading login page\n");
    if (!window) {
        logger_fatal("Application window was not created"
                     " before trying to show screen\n");
        return -1;
    }

    char *path1 = mx_get_cur_dir();
    char *path = mx_strjoin(path1, LOGIN_HTML);

    set_handlers();
    webkit_web_view_load_uri(webview, path);

    free(path);
    free(path1);
    return 0;
}
