#include "client.h"

#include "data_exchange.h"
#include "requests.h"

#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    if (mx_init(argc, argv) < 0) {
        mx_printerr("Usage: ./uchat <ip_address> <port>\n");
        return -1;
    } else logger_info("Client initialized\n");
    int fd = mx_open_connection();

    if (fd == -1) return -1;
    if (fd == -2) {
        logger_error("connection failed\n");
        if (!mx_isdb_valid()) {
            // load static page showing error
            if (mx_gui_network_error() < 0) {
                mx_close_connection(fd);
                return -1;
            }
            mx_start_gtk();
        } else {
            logger_warn("the app is running in offline mode\n");
            mx_db_init();
            if (mx_gui_login() < 0) {
                mx_close_connection(fd);
                return -1;
            }
            // ...
            mx_start_gtk();
            mx_db_finalize();
        }
    } else {
        logger_info("connection opened\n");
        if (mx_gui_login() < 0) {
            mx_close_connection(fd);
            return -1;
        }
        // ...
        t_registration_request *reg = malloc(sizeof(t_registration_request));
        reg->username = "admin";
        reg->password = "a";
        reg->phone = NULL;
        reg->email = "admin@example.com";
//        reg->email = NULL;
        reg->action = "register";
        t_request *req = malloc(sizeof(t_request));
        req->data = reg;
        req->action = REGISTRATION;
        char *registration_data = mx_create_request(req);
        free(req);
        free(reg);

        printf("send result: %d\n",mx_send_data(fd, registration_data));
        char *response = NULL;
        mx_receive_data(fd, &response);
        printf("response: %s\n", response);
        mx_start_gtk();
        mx_close_connection(fd);
        mx_db_finalize();
    }
    return 0;
}
