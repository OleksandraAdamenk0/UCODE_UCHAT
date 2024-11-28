#include "data_caching.h"

void mx_create_client_tables(sqlite3 *db) {
    char *sqlite_error = NULL;
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

    if (sqlite3_exec(db, sql_chats, 0, 0, &sqlite_error) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "SQL error: %s\n", sqlite_error);
        logger_error(err_msg);
    } else {
        logger_info("chats table created successfully.\n");
    }

    if (sqlite3_exec(db, sql_messages, 0, 0, &sqlite_error) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "SQL error: %s\n", sqlite_error);
        logger_error(err_msg);
    } else {
        logger_info("messages table created successfully.\n");
    }

    if (sqlite3_exec(db, sql_contacts, 0, 0, &sqlite_error) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "SQL error: %s\n", sqlite_error);
        logger_error(err_msg);
    } else {
        logger_info("contacts table created successfully.\n");
    }

    if (sqlite3_exec(db, sql_settings, 0, 0, &sqlite_error) != SQLITE_OK) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "SQL error: %s\n", sqlite_error);
        logger_error(err_msg);
    } else {
        logger_info("settings table created successfully.\n");
    }
}
