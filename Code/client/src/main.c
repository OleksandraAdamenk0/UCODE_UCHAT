#include "client.h"

#include "data_exchange.h"
#include "requests.h"

#include <stdio.h>
#include <unistd.h>

bool online;

static int to_login(int argc, const char *argv[]) {
    if (mx_create_app("login") < 0) return -1;
    logger_info("Gui initialized\n");
    return mx_run_app(argc, argv);
}

static int to_error(int argc, const char *argv[]) {
    if (mx_create_app("network_error") < 0) return -1;  // gtk init
    logger_info("Gui initialized\n");
    return mx_run_app(argc, argv);  // load static page showing error
}

int main(int argc, const char *argv[]) {
    if (mx_init(argc, argv) < 0) {
        mx_printerr("Usage: ./uchat <ip_address> <port>\n");
        return -1;
    } else logger_info("Client initialized\n");

    int status;

    int fd = mx_open_connection();
    if (fd == -1) return -1;
    if (fd == -2) {
        logger_error("Connection failed. Running offline mode\n");
        online = false;

        if (mx_isdb_valid()) {
            if (mx_db_init() < 0) {
                logger_warn("Failed to load local database\n");
                status = to_error(argc, argv);
            }
            status = to_login(argc, argv);
        } else status = to_error(argc, argv);
    } else {
        logger_info("Connection opened. Running online mode\n");
        online = true;
        status = to_login(argc, argv);
        mx_db_finalize();
    }
    return status;
}


// ...
//        t_registration_request *reg = malloc(sizeof(t_registration_request));
//        reg->username = "admin";
//        reg->password = "a";
//        reg->phone = NULL;
//        reg->email = "admin@example.com";
////        reg->email = NULL;
//        reg->action = "register";
//        t_request *req = malloc(sizeof(t_request));
//        req->data = reg;
//        req->action = REGISTRATION;
//        char *registration_data = mx_create_request(req);
//        free(req);
//        free(reg);
//
//        printf("send result: %d\n",mx_send_data(fd, registration_data));
//        char *response = NULL;
//        mx_receive_data(fd, &response);
//        printf("response: %s\n", response);