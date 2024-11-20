//
// Created by oleksandra on 17/11/24.
//


#include "client.h"
#include "connection.h"

void debug_send(int fd, char *str) {
    // Отправляем строку на сервер
    if (send(fd, str, strlen(str), 0) < 0) {
        perror("Error sending message");
        logger_error("error sending message\n");
        return;
    }

    printf("Message sent: %s\n", str);

    // Буфер для получения ответа от сервера
    char buffer[1024];
    int bytes_received = recv(fd, buffer, sizeof(buffer) - 1, 0);

    if (bytes_received < 0) {
        perror("Error receiving response");
        return;
    }

    buffer[bytes_received] = '\0';  // Завершаем строку нулевым символом

    // Выводим ответ от сервера
    printf("Response from server: %s\n", buffer);
}
