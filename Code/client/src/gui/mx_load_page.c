//
// Created by oleksandra on 04/12/24.
//

#include "gui.h"
#include "logger.h"
#include "libmx.h"
#include "utils.h"

static char *get_html_name(t_pages page) {
    if (page == LOAD_PAGE) return LOAD_HTML;
    if (page == LOGIN_PAGE) return LOGIN_HTML;
    if (page == ERROR_PAGE) return ERROR_HTML;
    if (page == CHATS_PAGE) return CHATS_HTML;
    if (page == REGISTRATION_PAGE) return REGISTRATION_HTML;
    return NULL;
}

static set_handlers_ptr get_setter(t_pages page) {
    if (page == LOAD_PAGE) return mx_load_handlers;
    if (page == LOGIN_PAGE) return mx_login_handlers;
    if (page == ERROR_PAGE) return mx_error_handlers;
    if (page == CHATS_PAGE) return mx_chats_handlers;
    if (page == REGISTRATION_PAGE) return mx_registration_handlers;
    return NULL;
}

int mx_load_page(t_pages page) {
    char *curdir = mx_curdir();
    if (curdir == NULL) {
        logger_fatal("mx_load_load_page: Failed to load html");
        logger_debug("mx_load_load_page: "
                     "Failed to get the path to the current directory");
        return -1;
    }
    char *HTML_path = mx_sprintf("%s%s", curdir, get_html_name(page));
    free(curdir);
    if (HTML_path == NULL) {
        logger_fatal("mx_load_load_page: Failed to load html");
        logger_debug("mx_load_load_page: Failed to get the path to the html");
        return -1;
    }

    set_handlers_ptr func = get_setter(page);

    if (func() < 0) {
        logger_fatal("mx_load_load_page: Failed to set handlers");
        free(HTML_path);
        return -1;
    }

    webkit_web_view_load_uri(webview, HTML_path);
    free(HTML_path);
    return 0;
}
