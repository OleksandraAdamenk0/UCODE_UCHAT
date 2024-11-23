#include "data_caching.h"

void mx_create_client_tables(sqlite3 *db) {
    char *errMsg = 0;
    const char *sql_chats =
        "CREATE TABLE IF NOT EXISTS chats (" \
        "chat_id INTEGER PRIMARY KEY," \
        "chat_name TEXT NOT NULL," \
        "last_message TEXT," \
        "photo BLOB);";

    const char *sql_messages =
        "CREATE TABLE IF NOT EXISTS messages (" \
        "id INTEGER PRIMARY KEY," \
        "receiver INTEGER NOT NULL," \
        "sender TEXT NOT NULL," \
        "timestamp DATETIME," \
        "binary BLOB," \
        "message TEXT," \
        "FOREIGN KEY(receiver) REFERENCES chats(chat_id));";

    const char *sql_contacts =
        "CREATE TABLE IF NOT EXISTS contacts (" \
        "username TEXT PRIMARY KEY," \
        "photo BLOB);";

    const char *sql_settings =
        "CREATE TABLE IF NOT EXISTS settings(" \
        "email TEXT PRIMARY KEY," \
        "phone TEXT," \
        "photo BLOB," \
        "theme TEXT);";

    if (sqlite3_exec(db, sql_chats, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("chats table created successfully.\n");
    }

    if (sqlite3_exec(db, sql_messages, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("messages table created successfully.\n");
    }

    if (sqlite3_exec(db, sql_contacts, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("contacts table created successfully.\n");
    }

    if (sqlite3_exec(db, sql_settings, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("settings table created successfully.\n");
    }
}
