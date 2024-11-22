//
// created by herman on 22/11/24.
//

#include "client.h"
#include "connection.h"

void receive_data(int sock, char *buffer, size_t buffer_size) 
{
    size_t received = 0;
    ssize_t bytes_received;

    while (received < buffer_size)
    {
        bytes_received = recv(sock, buffer + received, buffer_size - received, 0);

        if (bytes_received == -1)
        {
            logger_error("Error while receiving data");
            return;
        }

        if (bytes_received == 0) break; // connection closed
        
        received += bytes_received;
    }
}

void receive_data_with_length(int sock, char **buffer)
{
    size_t data_size;

    // first get the data size
    ssize_t bytes_received = recv(sock, &data_size, sizeof(data_size), 0);
    if (bytes_received == -1)
    {
        logger_error("Error receiving data size");
        return;
    }

    if (bytes_received == 0) 
    {
        logger_error("Connection closed before receiving data size");
        return;
    }

    // allocate memory for data
    *buffer = (char *)malloc(data_size);
    if (*buffer == NULL)
    {
        logger_error("Memory allocation failed for received data");
        return;
    }

    // get the data
    receive_data(sock, *buffer, data_size);
}
