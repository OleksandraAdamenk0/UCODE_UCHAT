#include <stdio.h>
#include <sqlite3.h>
#include <string.h>

#define BUFFER_SIZE 1024

void create_tables(sqlite3 *db);

int main(void) {
    sqlite3 *db;
    int rc;

    rc = sqlite3_open("messenger.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    // Create tables
    create_tables(db);

    sqlite3_close(db);
    return 0;
}

void create_tables(sqlite3 *db) {
    char *errMsg = 0;
    const char *sql_chats =
        "CREATE TABLE IF NOT EXISTS Chats (" \
        "chat_id INTEGER PRIMARY KEY AUTOINCREMENT," \
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

    // Execute SQL statements
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

void insert_chat(sqlite3 *db, const char *chat_name) {
    char *errMsg = 0;
    char sql[256];

    snprintf(sql, sizeof(sql), "INSERT INTO Chats (chat_name) VALUES ('%s');", chat_name);

    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Chat '%s' inserted successfully.\n", chat_name);
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

void insert_contact(sqlite3 *db, const char *name, const char *phone) {
    char *errMsg = 0;
    char sql[512];

    snprintf(sql, sizeof(sql), "INSERT INTO Contacts (name, phone) VALUES ('%s', '%s');", name, phone);

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
