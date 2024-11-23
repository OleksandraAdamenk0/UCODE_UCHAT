//
// created by herman on 22/11/24.
//

#include "connection.h"

void send_data(int sock, char *data, size_t data_size)
{
    size_t sent = 0;
    size_t chunk_size = 1024;  // data block size

    while (sent < data_size)
    {
        size_t to_send = (data_size - sent) < chunk_size ? (data_size - sent) : chunk_size;
        ssize_t bytes_sent = send(sock, data + sent, to_send, 0);

        if (bytes_sent == -1)
        {
            logger_error("Error sending data");
            return;
        }

        if (bytes_sent == 0)
        {
            logger_error("Connection closed during data send");
            return;
        }

        sent += bytes_sent;
    }
}

void send_data_with_length(int sock, char *data, size_t data_size)
{
    // send the data size first
    printf("Sending data size: %zu\n", data_size);  
    send(sock, &data_size, sizeof(data_size), 0);

    // then send the data itself
    printf("Sending data: %s\n", data);
    send_data(sock, data, data_size);
}

