#include "client.h"

int main(void) {
    // printf("Hello, World!\n");

    int sockfd = create_socket();
    if (sockfd < 0)
    {
        mx_printerr("Error creating socket\n");
        return -1;
    }
    else
    {
        mx_printstr("Socket was createt successfully\n");
    }


    if (connect_to_server(sockfd, SERVER_IP, SERVER_PORT) < 0) {
        mx_printerr("Error connecting to server\n");
        close_connection(sockfd);
        return 1;
    }

    // mx_printstr("Connected to server\n\n\n");

    // char message[1024];
    //  while (1) {
    //     mx_printstr("Enter message (or 'exit' to quit): ");
    //     fgets(message, sizeof(message), stdin);

    //     for (size_t i = 0; i < sizeof(message); i++) {
    //         if (message[i] == '\n') {
    //             message[i] = '\0';
    //             break;
    //         }
    //     }

    //     if (mx_strcmp(message, "exit") == 0) {
    //         break; 
    //     }

    //     // Send a message to the server
    //     if (send_data(sockfd, message) < 0) {
    //         mx_printerr("Error sending data\n");
    //         break;
    //     }

    //     printf("Message sent: %s\n", message);
    // }


    char client_id[50];
    // Getting ID from the server
    recv(sockfd, client_id, sizeof(client_id), 0);
    printf("Connected to server as: %s\n", client_id);

    char message[1024];
    while (1) {
        mx_printstr("Enter message (or 'exit' to quit): ");
        fgets(message, sizeof(message), stdin);

        for (size_t i = 0; i < sizeof(message); i++) {
            if (message[i] == '\n') {
                message[i] = '\0';
                break;
            }
        }

        if (mx_strcmp(message, "exit") == 0) {
            break; 
        }

        if (send_data(sockfd, message) < 0) {
            mx_printerr("Error sending data\n");
            break;
        }

        printf("[%s] Message sent: %s\n", client_id, message);
    }

    close_connection(sockfd);
    mx_printstr("Connection closed.\n");
    

    return 0;
}
