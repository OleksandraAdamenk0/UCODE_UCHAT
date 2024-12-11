//
// Created by oleksandra on 04/12/24.
//
#include "gui.h"
#include "logger.h"
#include "libmx.h"

static void submit_registration_form(WebKitUserContentManager *manager,
                          WebKitJavascriptResult *js_result,
                          gpointer user_data);

static void go_to_login(WebKitUserContentManager *manager,
                      WebKitJavascriptResult *js_result,
                      gpointer user_data);

int mx_registration_handlers() {
    if (!webkit_user_content_manager_register_script_message_handler(manager, "goToLogin")) {
        logger_error("set_handlers: Failed to register 'goToLogin' handler");
        return -1;
    }
    if (g_signal_connect(manager, "script-message-received::goToLogin", G_CALLBACK(go_to_login), NULL) == 0) {
        logger_error("set_handlers: Failed to connect 'go_to_login' signal");
        return -1;
    }
    if (!webkit_user_content_manager_register_script_message_handler(manager, "submitRegistrationForm")) {
        logger_error("set_handlers: Failed to register 'submitRegistrationForm' handler");
        return -1;
    }
    if (g_signal_connect(manager, "script-message-received::submitRegistrationForm", G_CALLBACK(submit_registration_form), NULL) == 0) {
        logger_error("set_handlers: Failed to connect 'submit_registration_form' signal");
        return -1;
    }
    logger_debug("mx_load_login_page: Handlers set for the page");
    return 0;

}

static void clear_handlers() {
    webkit_user_content_manager_unregister_script_message_handler(manager, "submitRegistrationForm");
    webkit_user_content_manager_unregister_script_message_handler(manager, "goToLogin");
    logger_debug("All handlers cleared.\n");
}

static void submit_registration_form(WebKitUserContentManager *manager,
                          WebKitJavascriptResult *js_result,
                          gpointer user_data) {
    logger_info("Registration form submitted\n");
//    JSCValue *value = webkit_javascript_result_get_js_value(js_result);
//    if (!jsc_value_is_string(value)) {
//        logger_debug("Error: Expected a JSON string from JavaScript!\n");
//        clear_handlers();
//        mx_load_error_page();
//        return;
//    }
//
//    gchar *json_data = jsc_value_to_string(value);
//    logger_debug("Received JSON for registration\n");
//
//    t_response *response = malloc(sizeof(t_response));
//    int status = mx_handle_request((char *)json_data, REGISTRATION, &response);
//    g_free(json_data);
//
//    if (!response) {
//        logger_error("Response from server is empty\n");
//        clear_handlers();
//        mx_load_error_page();
//        return;
//    }
//
//    if (response->status == 0) {
//        t_registration_response *data = response->data;
//        id = mx_atoi(data->tokens[0]);
//        free(data);
//        free(response);
//        clear_handlers();
//        mx_load_chat_page();
//        return;
//    } else if (response->status <= -9) {
//        clear_handlers();
//        free(response);
//        mx_load_error_page();
//        return;
//    }
//    char *cmd;
//    if (response->status == -1) {
//        cmd = mx_create_js_func_call("emptyUsername", response->msg);
//    } else if (response->status == -2) {
//        cmd = mx_create_js_func_call("registeredUsername", response->msg);
//    } else if (response->status == -3) {
//        cmd = mx_create_js_func_call("wrongPasswordFormat", response->msg);
//    } else if (response->status == -4) {
//        cmd = mx_create_js_func_call("emptyContacts", response->msg);
//    } else if (response->status == -5) {
//        cmd = mx_create_js_func_call("wrongPhoneFormat", response->msg);
//    } else if (response->status == -6) {
//        cmd = mx_create_js_func_call("wrongEmailFormat", response->msg);
//    } else if (response->status == -7) {
//        cmd = mx_create_js_func_call("registeredEmail", response->msg);
//    } else if (response->status == -8) {
//        cmd = mx_create_js_func_call("registeredPhone", response->msg);
//    }
//    printf("%s\n", cmd);
//    webkit_web_view_run_javascript(webview, "cleanErrors();" , NULL, NULL, NULL);
//    webkit_web_view_run_javascript(webview, cmd, NULL, NULL, NULL);
//    free(response);
//    free(cmd);
    return;

}

static void go_to_login(WebKitUserContentManager *manager,
                      WebKitJavascriptResult *js_result,
                      gpointer user_data) {
    logger_info("Login link pressed\n");
    clear_handlers();
    mx_load_page(LOGIN_PAGE);
}
