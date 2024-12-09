#include "server.h"
#include "database_managment.h"

t_list *get_all_contacts(sqlite3 *db) {
    sqlite3_stmt *stmt;
    t_list *contacts_list = NULL;
    char *sql = "SELECT * FROM contacts";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        char err_msg[256];
        printf(err_msg, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        //logger_error(err_msg);
        return NULL;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        t_get_contacts contact;
        contact.username = (char*)sqlite3_column_text(stmt, 0);
        contact.photo = (char*)sqlite3_column_blob(stmt, 1);
        mx_push_front(&contacts_list, &contact);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        char err_msg[256];
        snprintf(err_msg, sizeof(err_msg), "Execution failed: %s\n", sqlite3_errmsg(db));
        logger_error(err_msg);
    }
    sqlite3_finalize(stmt);
    return contacts_list;
}
