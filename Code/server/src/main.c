#include "server.h"

int main(int argc, const char * argv[]) {
    if (mx_init_server(argc, argv) == -1) {
      mx_printerr("Usage: ./uchat_server <port>\n");
    }

    // int server_fd;
    // struct sockaddr_in server_addr;
    // int addrlen = sizeof(server_addr);

    // if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    //     mx_printerr("Error creating socket\n");
    //     exit(EXIT_FAILURE);
    // }

    // server_addr.sin_family = AF_INET;
    // server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // server_addr.sin_port = htons(8080);

    // if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    //     mx_printerr("Error binding socket\n");
    //     exit(EXIT_FAILURE);
    // }

    // if (listen(server_fd, 3) < 0) {
    //     mx_printerr("Listening error\n");
    //     exit(EXIT_FAILURE);
    // }

    // mx_printstr("The server is waiting for connections on localhost:8080...\n");

    // while (1) {
    //     int *new_socket = malloc(sizeof(int));
    //     if ((*new_socket = accept(server_fd, (struct sockaddr *)&server_addr, (socklen_t *)&addrlen)) < 0) {
    //         mx_printerr("Error accepting connection\n");
    //         free(new_socket);
    //         continue;
    //     }

    //     mx_printstr("Client connected.\n");

    //     // Create a new thread for the client
    //     pthread_t client_thread;
    //     if (pthread_create(&client_thread, NULL, mx_handle_client, new_socket) != 0) {
    //         perror("Error creating thread");
    //         free(new_socket);
    //         continue;
    //     }

    //     // Separate the thread so that it terminates on its own
    //     pthread_detach(client_thread);
    // }

    // close(server_fd);

    return 0;
}
