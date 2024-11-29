//
// Created by oleksandra on 21/11/24.
//

#include "gui.h"
#include "logger.h"

int mx_load_error_page() {
    logger_debug("load error page\n");
    if (!window) {
        logger_fatal("application window was not created"
                     " before trying to show screen\n");
        return -1;
    }

    char *path1 = mx_get_cur_dir();
    char *path = mx_strjoin(path1, NETWORK_ERROR_HTML);
    free(path1);

    webkit_web_view_load_uri(webview, path);
    free(path);
    return 0;
}
