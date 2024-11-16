#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cjson/cJSON.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void create_tables(sqlite3 *db);
void create_chat(sqlite3 *db, const char *chat_name, int connection_status, int socket);
void send_message(sqlite3 *db, int chat_id, const char *sender, const char *content, int connection_status, int socket);
void add_contact(sqlite3 *db, const char *name, const char *phone, int connection_status, int socket);
void read_chat(sqlite3 *db, int chat_id);
void read_contacts(sqlite3 *db);
void send_message_to_server(cJSON *json, int socket);
void send_chat_to_server(cJSON *json, int socket);

int main(int argc, char *argv[]) {
    sqlite3 *db = NULL;

    int rc = sqlite3_open("messenger.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    create_tables(db);

    int sock = 0;
    struct sockaddr_in serv_addr;
    // char *message = "Hello from client!";
    // char buffer[BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    int connection_status = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (connection_status < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    if (strcmp(argv[1], "create_chat") == 0) {
        if (argc != 3) {
            printf("Wrong number of arguments\n");
            sqlite3_close(db);
            close(sock);
            exit(1);
        }
        create_chat(db, argv[2], connection_status < 0 ? 0 : 1, sock);
    } else if (strcmp(argv[1], "send_message") == 0) {
        if (argc != 5) {
            printf("Wrong number of arguments\n");
            sqlite3_close(db);
            close(sock);
            exit(1);
        }
        send_message(db, atoi(argv[2]), argv[3], argv[4], connection_status < 0 ? 0 : 1, sock);
    } else if (strcmp(argv[1], "add_contact") == 0) {
        if (argc != 4) {
            printf("Wrong number of arguments\n");
            sqlite3_close(db);
            close(sock);
            exit(1);
        }
        add_contact(db, argv[2], argv[3], connection_status < 0 ? 0 : 1, sock);
    } else if (strcmp(argv[1], "read_chat") == 0) {
        if (argc != 3) {
            printf("Wrong number of arguments\n");
            sqlite3_close(db);
            close(sock);
            exit(1);
        }
        read_chat(db, atoi(argv[2]));
    } else if (strcmp(argv[1], "contacts_list") == 0) {
        read_contacts(db);
    } else {
        printf("Unknown command");
        sqlite3_close(db);
        close(sock);
        exit(1);
    }

    sqlite3_close(db);
    close(sock);
    return 0;
}

void create_tables(sqlite3 *db) {
    char *errMsg = 0;
    const char *sql_chats =
        "CREATE TABLE IF NOT EXISTS Chats (" \
        "chat_id INTEGER PRIMARY KEY AUTOINCREMENT," \
        "chat_name TEXT NOT NULL," \
        "last_message TEXT," \
        "status INTEGER NOT NULL DEFAULT 0," \
        "last_timestamp DATETIME);";

    const char *sql_messages =
        "CREATE TABLE IF NOT EXISTS Messages (" \
        "message_id INTEGER PRIMARY KEY AUTOINCREMENT," \
        "chat_id INTEGER," \
        "sender TEXT NOT NULL," \
        "content TEXT NOT NULL," \
        "status INTEGER NOT NULL DEFAULT 0," \
        "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP," \
        "FOREIGN KEY(chat_id) REFERENCES Chats(chat_id));";

    const char *sql_contacts =
       "CREATE TABLE IF NOT EXISTS Contacts (" \
       "contact_id INTEGER PRIMARY KEY AUTOINCREMENT," \
       "name TEXT NOT NULL," \
       "status INTEGER NOT NULL DEFAULT 0," \
       "phone TEXT UNIQUE," \
       "chat_id INTEGER," \
       "FOREIGN KEY(chat_id) REFERENCES Chats(chat_id));";

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

void create_chat(sqlite3 *db, const char *chat_name, int connection_status, int socket) {
    char *errMsg = 0;
    char sql[256];

    snprintf(sql, sizeof(sql), "INSERT INTO Chats (chat_name, status) VALUES ('%s', %d);", chat_name, connection_status);

    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);

    } else {
        printf("Chat '%s' inserted successfully.\n", chat_name);
    }

    int chat_id = sqlite3_last_insert_rowid(db);
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "action", "create_chat");
    cJSON_AddNumberToObject(json, "chat_id", chat_id);
    cJSON_AddStringToObject(json, "chat_name", chat_name);

    send_chat_to_server(json, socket);
}

void send_chat_to_server(cJSON *json, int socket) {
    char *json_str = cJSON_Print(json);
    char buffer[BUFFER_SIZE] = {""};

    send(socket, json_str, strlen(json_str), 0);
    printf("Message sent to server\n");

    read(socket, buffer, BUFFER_SIZE);
    printf("Response from server: %s\n", buffer);
    cJSON *response = cJSON_Parse(buffer);
    cJSON *status = cJSON_GetObjectItemCaseSensitive(response, "status");
    cJSON *message = cJSON_GetObjectItemCaseSensitive(response, "message");
    printf("server response:\nstatus - %s\nmessage - %s", status->valuestring, message->valuestring);
}

void send_message(sqlite3 *db, int chat_id, const char *sender, const char *content, int connection_status, int socket) {
    char *errMsg = 0;
    char sql[512];

    snprintf(sql, sizeof(sql), "INSERT INTO Messages (chat_id, sender, content, status) VALUES (%d, '%s', '%s', %d);", chat_id, sender, content, connection_status);

    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Message from '%s' inserted successfully.\n", sender);
    }

    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "action", "send_message");
    cJSON_AddNumberToObject(json, "chat_id", chat_id);
    cJSON_AddStringToObject(json, "sender_id", sender);
    cJSON_AddStringToObject(json, "content", content);

    send_message_to_server(json, socket);

    cJSON_Delete(json);
}

void send_message_to_server(cJSON *json, int socket) {
    char *json_str = cJSON_Print(json);
    char buffer[BUFFER_SIZE] = {""};

    send(socket, json_str, strlen(json_str), 0);
    printf("Message sent to server\n");

    read(socket, buffer, BUFFER_SIZE);
    printf("Response from server: %s\n", buffer);
    cJSON *response = cJSON_Parse(buffer);
    cJSON *status = cJSON_GetObjectItemCaseSensitive(response, "status");
    cJSON *message = cJSON_GetObjectItemCaseSensitive(response, "message");
    printf("server response:\nstatus - %s\nmessage - %s", status->valuestring, message->valuestring);
}

void delete_table(sqlite3 *db, const char *table_name) {
    char *errMsg = 0;
    char sql[256];

    snprintf(sql, sizeof(sql), "DROP TABLE IF EXISTS %s", table_name);

    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Table deleted successfully\n");
    }
}

void read_chat(sqlite3 *db, int chat_id) {
    char sql[256];
    char *response = NULL;
    sqlite3_stmt *stmt;

    // Prepare the SQL statement to select messages for the given chat_id
    snprintf(sql, sizeof(sql), "SELECT * FROM Messages WHERE chat_id = %d;", chat_id);

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt , 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Execute the statement and print the results
    snprintf(response, BUFFER_SIZE, "Messages for chat_id %d:\n", chat_id);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int message_id = sqlite3_column_int(stmt, 0);
        const char *sender = (const char *)sqlite3_column_text(stmt, 2);
        const char *content = (const char *)sqlite3_column_text(stmt, 3);
        const char *timestamp = (const char *)sqlite3_column_text(stmt, 4);

        snprintf(response + strlen(response), BUFFER_SIZE - strlen(response),
                 "Message ID: %d, Sender: %s, Content: %s, Timestamp: %s\n",
                 message_id, sender, content, timestamp);
    }

    // Finalize the statement to release resources
    sqlite3_finalize(stmt);
}

void add_contact(sqlite3 *db, const char *name, const char *phone, int connection_status, int socket) {
    char *errMsg = 0;
    char sql[512];

    snprintf(sql, sizeof(sql), "INSERT INTO Contacts (name, phone, status) VALUES ('%s', '%s', %d);", name, phone, connection_status);

    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        if (sqlite3_errcode(db) == SQLITE_CONSTRAINT) {
            fprintf(stderr, "Error: Phone number '%s' already exists.\n", phone);
        } else {
            fprintf(stderr, "SQL error: %s\n", errMsg);
        }
        sqlite3_free(errMsg);
    } else {
        create_chat(db, name, connection_status, socket);
        printf("Contact '%s' added successfully.\n", name);
    }


}

void read_contacts(sqlite3 *db) {
    const char *sql = "SELECT * FROM Contacts;";
    char *response = NULL;
    sqlite3_stmt *stmt;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Execute the statement and print the results
    snprintf(response, BUFFER_SIZE, "Contacts:\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int contact_id = sqlite3_column_int(stmt, 0);
        const char *name = (const char *)sqlite3_column_text(stmt, 1);
        const char *phone = (const char *)sqlite3_column_text(stmt, 2);

        snprintf(response + strlen(response), BUFFER_SIZE - strlen(response),
                 "Contact ID: %d, Name: %s, Phone: %s\n",
                 contact_id, name, phone);
    }

    // Finalize the statement to release resources
    sqlite3_finalize(stmt);
}
