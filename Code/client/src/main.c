#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8082
#define BUFFER_SIZE 1024

int main(void) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *message = "Hello from client!";
    char buffer[BUFFER_SIZE] = {0};

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

    send(sock, message, strlen(message), 0);
    printf("Message sent to server\n");

    read(sock, buffer, BUFFER_SIZE);
    printf("Response from server: %s\n", buffer);

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

void insert_chat(sqlite3 *db, const char *chat_name, int connection_status) {
    char *errMsg = 0;
    char sql[256];

    snprintf(sql, sizeof(sql), "INSERT INTO Chats (chat_name, status) VALUES ('%s', %d);", chat_name, connection_status);

    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Chat '%s' inserted successfully.\n", chat_name);
    }
}

void insert_message(sqlite3 *db, int chat_id, const char *sender, const char *content, int connection_status) {
    char *errMsg = 0;
    char sql[512];

    snprintf(sql, sizeof(sql), "INSERT INTO Messages (chat_id, sender, content, status) VALUES (%d, '%s', '%s', %d);", chat_id, sender, content, connection_status);

    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Message from '%s' inserted successfully.\n", sender);
    }
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

void read_chat(sqlite3 *db, int chat_id, char *response) {
    char sql[256];
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

void insert_contact(sqlite3 *db, const char *name, const char *phone, int connection_status) {
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
        printf("Contact '%s' added successfully.\n", name);
    }
}

void read_contacts(sqlite3 *db, char *response) {
    const char *sql = "SELECT * FROM Contacts;";
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
