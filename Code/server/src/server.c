#include "server.h"

// void *handle_client(void *client_socket) {
//     int sock = *(int *)client_socket;
//     free(client_socket);

//     char buffer[1024];
//     while (1) {
//         int bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
//         if (bytes_received > 0) {
//             buffer[bytes_received] = '\0';
//             printf("Message from client: %s\n", buffer);
//         } else if (bytes_received == 0) {
//             mx_printstr("Client disconnected.\n");
//             break;
//         } else {
//             mx_printerr("Error receiving data");
//             break;
//         }
//     }

//     close(sock);
//     return NULL;
// }

void *handle_client(void *socket_ptr) {
    int client_socket = *(int *)socket_ptr;
    free(socket_ptr);

    // Generating a unique client ID
    char client_id[50];
    snprintf(client_id, sizeof(client_id), "Client_%d", client_socket);

    // Greeting the client indicating his ID
    send(client_socket, client_id, strlen(client_id), 0);

    char buffer[1024];
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            printf("[%s]: %s\n", client_id, buffer);
        } else if (bytes_received == 0) {
            printf("[%s]: Disconnected\n", client_id);
            break;
        } else {
            perror("Error receiving data");
            break;
        }
    }

    close(client_socket);
    return NULL;
}

