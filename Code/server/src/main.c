#include "../inc/server.h"

#define BACKLOG 5

int main(int argc, const char * argv[]) {
    if (mx_init_server(argc, argv) == -1) {
      mx_printerr("Usage: ./uchat_server <port>\n");
    }

    // if (mx_open_connection() < 0) return -1;
    // else logger_info("connection opened\n");

    // mx_accept_connections();

    
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char *message = "Hello from server!";

    // Создание серверного сокета
    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Можно заменить на inet_addr("127.0.0.1") для локального
    server_addr.sin_port = htons(atoi(argv[1]));

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        return 1;
    }

    if (listen(server_sock, BACKLOG) == -1) {
        perror("Listen failed");
        return 1;
    }

    printf("Server is waiting for a connection...\n");

    // Принятие соединения от клиента
    if ((client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len)) == -1) {
        perror("Accept failed");
        return 1;
    }

    printf("Client connected.\n");

    // Отправка данных с использованием функции send_data_with_length
    printf("Sending message of size: %zu\n", strlen(message));
    send_data_with_length(client_sock, message, strlen(message));

    // Закрытие соединения
    printf("Data sent, closing connection.\n");
    close(client_sock);
    close(server_sock);

    return 0;
}
