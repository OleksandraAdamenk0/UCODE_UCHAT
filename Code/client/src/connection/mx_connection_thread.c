//
// Created by oleksandra on 17/11/24.
//

#include "connection.h"
#include "data_caching.h"
#include "logger.h"
#include "client.h"
#include "gui.h"

int fd;
int mode;

static void set_online_mode() {
    logger_info("Connection succeeded. Running online mode");
    mode = 0;
    if (mx_create_tables() < 0){
        logger_error("set_online_mode: Failed to update local db");
        mode = -2;
        return;
    }
}

static void set_offline_mode() {
    logger_info("Connection failed. Running offline mode");
    mode = -1;
    if (mx_is_db_valid() < 0) {
        logger_error("Local DB is unavailable.\n");
        mode = -2;
        return;
    }
}

void *mx_connection_thread(void *arg) {
    fd = mx_open_connection();

    if (fd > 0) set_online_mode();
    else set_offline_mode();

    webkit_web_view_run_javascript(webview, "chooseMode();", NULL, NULL, NULL);
    return NULL;
}
