#include "bd.h"

void insert_data(sqlite3 *db) {
    const char *sql_chat = "INSERT INTO CHAT (chat_id, user_id) VALUES ('chat1', 'musteruser123');";

    const char *sql_lastseen = "INSERT INTO last_seen (user_id, timestamp) VALUES ('musteruser123', datetime('now'));";

    const char *sql_message = "INSERT INTO message (message_id, chat_id, timestamp, send_to_id, send_from_id, message)"
        	"VALUES ('m1234', 'chat1', datetime('now'), 'musteruser123', 'musteruser345', 'hello world!');";

    const char *sql_token = "INSERT INTO token (token, user_id, created_at, expires_at)"
        	"VALUES ('t54359', 'musteruser123', datetime('now'), datetime('now','+72 hours'));";

    const char *sql_user1 = "INSERT INTO user (user_id, username, contact, email, password)"
        	"VALUES ('musteruser123', 'politra', '+4915120512567', 'muster@gmai.com', 'pas111');";

    const char *sql_user2 = "INSERT INTO user (user_id, username, contact, email, password)"
        	"VALUES ('musteruser345', 'alexxx', '+4915160812507', 'muster1@gmai.com', '123456');";

    const char *sql_chat_user = "INSERT INTO chat_user (chat_id, user_id)"
        	"VALUES ('chat1', 'musteruser345');";

    if (execute_sql(db, sql_chat) != SQLITE_OK) return;
    if (execute_sql(db, sql_lastseen) != SQLITE_OK) return;
    if (execute_sql(db, sql_message) != SQLITE_OK) return;
    if (execute_sql(db, sql_token) != SQLITE_OK) return;
    if (execute_sql(db, sql_user1) != SQLITE_OK) return;
    if (execute_sql(db, sql_user2) != SQLITE_OK) return;
    if (execute_sql(db, sql_chat_user) != SQLITE_OK) return;

    mx_printstr("Chat table:\n");
    print_query_results(db, "SELECT * FROM chat;");
    mx_printstr("Last_seen table:\n");
    print_query_results(db, "SELECT * FROM last_seen;");
    mx_printstr("messege table:\n");
    print_query_results(db, "SELECT * FROM message;");
    mx_printstr("Token table:\n");
    print_query_results(db, "SELECT * FROM token;");
    mx_printstr("User table:\n");
    print_query_results(db, "SELECT * FROM user;");
    mx_printstr("User chat_user:\n");
    print_query_results(db, "SELECT * FROM chat_user;");
}

