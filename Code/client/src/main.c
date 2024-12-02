#include "client.h"
#include "initialization.h"
#include "connection.h"
#include "logger.h"
#include "gui.h"

int port;
char *ip;
long long int id = -1;
GtkApplication *app;

int main(int argc, const char *argv[]) {
    // arguments
    t_arguments *arguments = mx_parse_args(argc, argv);
    if (!arguments) {
        mx_printerr("Usage: ./uchat <ip_address> <port>\n");
        return -1;
    }

    // variables
    port = arguments->port;
    ip = arguments->ip;
    free(arguments);

    // logger
    if (logger_init(LOGGER_CONFIG) < 0) return -1;
    logger_info("Logger initialized\n");

    // gtk app
    app = gtk_application_new("com.campus.uchat", G_APPLICATION_HANDLES_COMMAND_LINE);
    if (app == NULL) {
        logger_fatal("Failed to create GTK app\n");
        return -1;
    }
    g_signal_connect(app, "activate", G_CALLBACK(mx_gui_init), NULL);
    g_signal_connect(app, "command-line", G_CALLBACK(mx_gui_init), NULL);

    mx_run_app(argc, argv);
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