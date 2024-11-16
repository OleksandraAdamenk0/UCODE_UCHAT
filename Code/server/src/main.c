#include <sqlite3.h>
#include <stdbool.h>
#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cjson/cJSON.h>

#define PORT 8080
#define BUFFER_SIZE 1024

cJSON *handle_request(sqlite3 *db, cJSON *request);
void create_tables(sqlite3 *db);
void insert_message(sqlite3 *db, int chat_id, const char *sender, const char *content);
void insert_chat(sqlite3 *db, const char *chat_name, int chat_id);

int main(void) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    sqlite3 *db = NULL;

    int rc = sqlite3_open("messenger_server.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    create_tables(db);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        read(new_socket, buffer, BUFFER_SIZE);
        cJSON *client_request = cJSON_Parse(buffer);
        if (client_request == NULL) {
            const char *error_ptr = cJSON_GetErrorPtr();
            if (error_ptr != NULL) {
                printf("Error: %s\n", error_ptr);
            }
            // cJSON_Delete(client_request);
            return 1;
        }

        cJSON *response = handle_request(db, client_request);
        char *response_str = cJSON_Print(response);

        // delete the JSON object
        cJSON_Delete(client_request);
        cJSON_Delete(response);
        send(new_socket, response_str, strlen(response_str), 0);
        printf("Response sent to client\n");

        close(new_socket);
    }

    close(server_fd);
    return 0;
}

cJSON *handle_request(sqlite3 *db, cJSON *request) {
    cJSON *action = cJSON_GetObjectItemCaseSensitive(request, "action");
    cJSON *response = cJSON_CreateObject();

    if (strcmp(action->valuestring, "send_message") == 0) {
        cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(request, "chat_id");
        cJSON *sender_id = cJSON_GetObjectItemCaseSensitive(request, "sender_id");
        cJSON *content = cJSON_GetObjectItemCaseSensitive(request, "content");
        insert_message(db, chat_id->valueint, sender_id->valuestring, content->valuestring);
        cJSON_AddStringToObject(response, "status", "0");
        cJSON_AddStringToObject(response, "message", "message sent successfully");
    } else if (strcmp(action->valuestring, "create_chat") == 0) {
        cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(request, "chat_id");
        cJSON *chat_name = cJSON_GetObjectItemCaseSensitive(request, "chat_name");
        insert_chat(db, chat_name->valuestring, chat_id->valueint);
        cJSON_AddStringToObject(response, "status", "0");
        cJSON_AddStringToObject(response, "chat", "chat created successfully");
    }

    return response;
}

void create_tables(sqlite3 *db) {
    char *errMsg = 0;
    const char *sql_chats =
        "CREATE TABLE IF NOT EXISTS Chats (" \
        "chat_id INTEGER PRIMARY KEY," \
        "chat_name TEXT NOT NULL," \
        "last_message TEXT," \
        "last_timestamp DATETIME);";

    const char *sql_messages =
        "CREATE TABLE IF NOT EXISTS Messages (" \
        "message_id INTEGER PRIMARY KEY AUTOINCREMENT," \
        "chat_id INTEGER," \
        "sender TEXT NOT NULL," \
        "content TEXT NOT NULL," \
        "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP," \
        "FOREIGN KEY(chat_id) REFERENCES Chats(chat_id));";

    const char *sql_contacts =
       "CREATE TABLE IF NOT EXISTS Contacts (" \
       "contact_id INTEGER PRIMARY KEY AUTOINCREMENT," \
       "name TEXT NOT NULL," \
       "phone TEXT UNIQUE);";

    if (sqlite3_exec(db, sql_chats, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Chats table created successfully.\n");
    }

    if (sqlite3_exec(db, sql_messages, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Messages table created successfully.\n");
    }

    if (sqlite3_exec(db, sql_contacts, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Contacts table created successfully.\n");
    }
}

void insert_message(sqlite3 *db, int chat_id, const char *sender, const char *content) {
    char *errMsg = 0;
    char sql[512];

    snprintf(sql, sizeof(sql), "INSERT INTO Messages (chat_id, sender, content) VALUES (%d, '%s', '%s');", chat_id, sender, content);

    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Message from '%s' inserted successfully.\n", sender);
    }

}

void insert_chat(sqlite3 *db, const char *chat_name, int chat_id) {
    char *errMsg = 0;
    char sql[256];

    snprintf(sql, sizeof(sql), "INSERT INTO Chats (chat_name, chat_id) VALUES ('%s', %d);", chat_name, chat_id);

    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);

    } else {
        printf("Chat '%s' inserted successfully.\n", chat_name);
    }
}
