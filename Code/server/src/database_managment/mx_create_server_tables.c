#include "database_managment.h"

void mx_create_server_tables(sqlite3 *db) {
    char *errMsg = 0;
    const char *sql_chats =
        "CREATE TABLE IF NOT EXISTS chats (" \
        "chat_id INTEGER PRIMARY KEY," \
        "chat_name TEXT NOT NULL," \
        "photo BLOB);";

    const char *sql_users =
        "CREATE TABLE IF NOT EXISTS users (" \
        "username TEXT PRIMARY KEY," \
        "password TEXT," \
        "email TEXT UNIQUE," \
        "phone TEXT UNIQUE," \
        "photo BLOB);";

    const char *sql_messages =
        "CREATE TABLE IF NOT EXISTS messages (" \
        "id INTEGER PRIMARY KEY," \
        "receiver INTEGER NOT NULL," \
        "sender TEXT NOT NULL," \
        "timestamp DATETIME," \
        "binary BLOB," \
        "message TEXT," \
        "FOREIGN KEY(receiver) REFERENCES chats(chat_id)," \
        "FOREIGN KEY(sender) REFERENCES users(username));";

    const char *sql_chats_users =
        "CREATE TABLE IF NOT EXISTS chats_users (" \
        "chat_id INTEGER," \
        "username TEXT," \
        "FOREIGN KEY(chat_id) REFERENCES chats(chat_id)," \
        "FOREIGN KEY(username) REFERENCES users(username));";

    if (sqlite3_exec(db, sql_chats, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("chats table created successfully.\n");
    }

    if (sqlite3_exec(db, sql_users, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("users table created successfully.\n");
    }

    if (sqlite3_exec(db, sql_messages, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("messages table created successfully.\n");
    }

    if (sqlite3_exec(db, sql_chats_users, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("chats_users table created successfully.\n");
    }
}
