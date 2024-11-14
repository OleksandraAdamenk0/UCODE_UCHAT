#include "bd.h"

int print_callback(void *not_used, int argc, char **argv, char **col_name) {
    (void)not_used;

    for (int i = 0; i < argc; i++) {
        mx_printstr(col_name[i]);
        mx_printstr(" = ");

        if (argv[i]) {
            mx_printstr(argv[i]);
        } else {
            mx_printstr("NULL");
        }
        mx_printstr("\n");
    }
    mx_printstr("\n");

    return 0;
}

int print_query_results(sqlite3 *db, const char *sql) {
    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, print_callback, 0, &err_msg);
    if (rc != SQLITE_OK) {
        mx_printerr("Error executing SELECT:");
        mx_printerr(err_msg);
        mx_printerr("\n");
        sqlite3_free(err_msg);
    }
    return rc;
}

int execute_sql(sqlite3 *db, const char *sql) {
    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        mx_printerr("Error SQL: ");
        mx_printerr(err_msg);
        mx_printerr("\n");
        sqlite3_free(err_msg);
    }
    return rc;
}
int main() {
    sqlite3 *db;
    int rc = sqlite3_open("messenger.db", &db);

    if (rc != SQLITE_OK) {
        mx_printerr("Can't open database: ");
        mx_printerr(sqlite3_errmsg(db));
        return 1;
    }

    // Chat
    const char *sql_create_chat =
        "CREATE TABLE IF NOT EXISTS chat ("
        "chat_id TEXT PRIMARY KEY," // or es a number with autoincriment
        "user_id TEXT NOT NULL,"
        "FOREIGN KEY(user_id) REFERENCES User(user_id)"
        ");";

    // LastSeen
    const char *sql_create_lastseen =
        "CREATE TABLE IF NOT EXISTS last_seen ("
        "user_id TEXT NOT NULL,"
        "timestamp DATETIME NOT NULL,"
        "FOREIGN KEY(user_id) REFERENCES User(user_id)"
        ");";

    //  Message
    const char *sql_create_message =
        "CREATE TABLE IF NOT EXISTS message ("
        "message_id TEXT PRIMARY KEY,"
        "chat_id TEXT NOT NULL,"
        "timestamp DATETIME NOT NULL,"
        "send_to_id TEXT NOT NULL,"
        "send_from_id TEXT NOT NULL,"
        "message BLOB NOT NULL,"
        "FOREIGN KEY(chat_id) REFERENCES chat(chat_id),"
        "FOREIGN KEY(send_to_id) REFERENCES user(user_id),"
        "FOREIGN KEY(send_from_id) REFERENCES user(user_id)"
        ");";

    // Token
    const char *sql_create_token =
        "CREATE TABLE IF NOT EXISTS token ("
        "token TEXT PRIMARY KEY,"
        "user_id TEXT NOT NULL,"
        "created_at DATETIME NOT NULL,"
        "expires_at DATETIME NOT NULL,"
        "FOREIGN KEY(user_id) REFERENCES user(user_id)"
        ");";

    //  User
    const char *sql_create_user =
        "CREATE TABLE IF NOT EXISTS user ("
        "user_id TEXT PRIMARY KEY,"
        "username TEXT NOT NULL UNIQUE,"
        "contact TEXT UNIQUE CHECK(LENGTH(contact) = 14),"
        "email TEXT UNIQUE,"
        "password TEXT NOT NULL" // the smallest length 6, letters and numbers (can be just numbers 6)
        ");";

    const char *sql_create_chat_user =
        "CREATE TABLE IF NOT EXISTS chat_user ("
        "chat_id TEXT NOT NULL,"
        "user_id TEXT NOT NULL,"
        "FOREIGN KEY(chat_id) REFERENCES chat(chat_id),"
        "FOREIGN KEY(user_id) REFERENCES user(user_id),"
        "UNIQUE(chat_id, user_id)"
        ");";

    if (execute_sql(db, sql_create_chat) != SQLITE_OK) return 1;
    if (execute_sql(db, sql_create_lastseen) != SQLITE_OK) return 1;
    if (execute_sql(db, sql_create_message) != SQLITE_OK) return 1;
    if (execute_sql(db, sql_create_token) != SQLITE_OK) return 1;
    if (execute_sql(db, sql_create_user) != SQLITE_OK) return 1;
    if (execute_sql(db, sql_create_chat_user) != SQLITE_OK) return 1;

    insert_data(db);
    sqlite3_close(db);
    return 0;
}

