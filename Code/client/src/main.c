#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, const char * argv[]) {
    if (mx_init(argc, argv) < 0) {
        mx_printerr("Usage: ./uchat <ip_address> <port>\n");
        return -1;
    }
    int fd = mx_open_connection();
    if (fd == -1) return -1;
    if (fd == -2) {
        logger_error("connection failed\n");
        logger_warn("the app is running in offline mode\n");

        // transition to offline mode logic here

    } else logger_info("connection opened\n");

    // ...
    // debug_send(fd, "test string\n");

    // mx_close_connection(fd);
    // logger_info("connection closed\n");
    // return 0;

    int sock;
    struct sockaddr_in server_addr;
    char *buffer = NULL;

    // Создание клиентского сокета
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));  // Преобразуем порт в число
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);  // IP-адрес из аргумента

    // Подключение к серверу
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        return 1;
    }

    printf("Connected to server.\n");

    // Прием данных с использованием функции receive_data_with_length
    printf("Receiving data...\n");
    receive_data_with_length(sock, &buffer);

    if (buffer != NULL) {
        printf("Received message: %s\n", buffer);
        free(buffer);  // Освобождение памяти
    } else {
        printf("Buffer is null\n");
    }

    // Закрытие соединения
    close(sock);
    return 0;
}
