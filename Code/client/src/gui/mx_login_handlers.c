#include "gui.h"
#include "utils.h"
#include "client.h"
#include "logger.h"
#include "libmx.h"
#include "data_exchange.h"
#include "data_caching.h"

static void submit_login_form(WebKitUserContentManager *manager,
                          WebKitJavascriptResult *js_result,
                          gpointer user_data);

static void go_to_register(WebKitUserContentManager *manager,
                         WebKitJavascriptResult *js_result,
                         gpointer user_data);

static bool validate_js_result(WebKitJavascriptResult *js_result, char **json_data);
static t_response *process_request(const char *json_data);
static void handle_login_response(t_response *response);

int mx_login_handlers() {
    if (!webkit_user_content_manager_register_script_message_handler(manager, "goToRegister")) {
        logger_error("set_handlers: Failed to register 'goToRegister' handler");
        return -1;
    }
    if (g_signal_connect(manager, "script-message-received::goToRegister", G_CALLBACK(go_to_register), NULL) == 0) {
        logger_error("set_handlers: Failed to connect 'go_to_register' signal");
        return -1;
    }
    if (!webkit_user_content_manager_register_script_message_handler(manager, "submitLoginForm")) {
        logger_error("set_handlers: Failed to register 'submitLoginForm' handler");
        return -1;
    }
    if (g_signal_connect(manager, "script-message-received::submitLoginForm", G_CALLBACK(submit_login_form), NULL) == 0) {
        logger_error("set_handlers: Failed to connect 'submit_login_form' signal");
        return -1;
    }
    logger_debug("mx_load_login_page: Handlers set for the page");
    return 0;

}

static void clear_handlers() {
    webkit_user_content_manager_unregister_script_message_handler(manager, "submitLoginForm");
    webkit_user_content_manager_unregister_script_message_handler(manager, "goToRegister");
    logger_debug("All handlers cleared.\n");
}

static void submit_login_form(WebKitUserContentManager *manager,
                          WebKitJavascriptResult *js_result,
                          gpointer user_data) {
    logger_info("Login form submitted\n");
    char *json_data = NULL;
    if (!validate_js_result(js_result, &json_data)) {
        clear_handlers();
        mx_load_page(ERROR_PAGE);
        return;
    }
    logger_debug("Received JSON for login\n");
    t_response *response = process_request(json_data);
    handle_login_response(response);
}

static void go_to_register(WebKitUserContentManager *manager,
                         WebKitJavascriptResult *js_result,
                         gpointer user_data) {
    logger_info("Register link pressed\n");
    clear_handlers();
    mx_load_page(REGISTRATION_PAGE);
}

static bool validate_js_result(WebKitJavascriptResult *js_result, char **json_data) {
    JSCValue *value = webkit_javascript_result_get_js_value(js_result);
    if (!jsc_value_is_string(value)) {
        logger_debug("Error: Expected a JSON string from JavaScript!\n");
        return false;
    }
    *json_data = (char *)jsc_value_to_string(value);
    return true;
}

static t_response *process_request(const char *json_data) {
    t_response *response = malloc(sizeof(t_response));
    int status = mx_handle_request((char *)json_data, LOGIN, &response);

    logger_debug(mx_itoa(response->status));

    if (status != 0 || !response) {
        logger_error("Error processing request or empty response\n");
        free(response);
        return NULL;
    }

    return response;
}

static void handle_login_response(t_response *response) {
    if (!response) {
        clear_handlers();
        mx_load_page(ERROR_PAGE);
        return;
    }

    logger_info(response->msg);

    if (response->status == 0) { // Success
        t_login_response *data = response->data;
        id = mx_atoi(data->tokens[0]);
        free(data);
        free(response);
        if (mode == 0) mx_update_db();
        clear_handlers();
        mx_load_page(CHATS_PAGE);
    } else if (response->status == -1) { // Invalid data
        char *cmd = mx_sprintf("invalidData('%s');", response->msg);
        logger_debug("Trying to call function invalidData from js");
        mx_load_page(LOGIN_PAGE);
        webkit_web_view_run_javascript(webview, cmd, NULL, NULL, NULL);
        logger_debug("Function invalidData from js was executed");
        free(cmd);
        free(response);
    } else { // Other errors
        clear_handlers();
        free(response);
        mx_load_page(ERROR_PAGE);
    }
}
