//
// Created by oleksandra on 14/11/24.
//

int post(const char *table_name,
          const char **column_names, int columns_amount,
          const char **values, int values_amount) {

    char *cmd = "INSERT INTO ";
    char *cmd_1, *cmd_2;
    cmd_1 = mx_strjoin(cmd, table_name);
    cmd_2 = mx_strjoin(cmd_1, " (");
    free(cmd_1);
    for (int i = 0; i < columns_amount; ++i) {
        cmd_1 = mx_strjoin(cmd_2, column_names[i]);
        free(cmd_2);
        if (i != columns_amount - 1) cmd_2 = mx_strjoin(cmd_1, ", ");
        else cmd_2 = mx_strdup(cmd_1);
        free(cmd_1);
    }

    cmd_1 = mx_strjoin(cmd_2, ") VALUES ('");
    free(cmd_2);

    for (int i = 0; i < values_amount; ++i) {
        cmd_2 = mx_strjoin(cmd_1, column_names[i]);
        free(cmd_1);
        if (i != columns_amount - 1) cmd_1 = mx_strjoin(cmd_2, "', '");
        else cmd_1 = mx_strjoin(cmd_2, "'")
        free(cmd_2);
    }

    cmd_2 = mx_strjoin(cmd_1, ");");
    free(cmd_1);

    if (execute_sql(db, cmd_2) != SQLITE_OK) return 0;
    else return -1;
}

int mx_post_last_seen(const char *user_id, const char *timestamp) {
    const char *columns[2] = { "user_id", "timestamp"};
    const char *values[2] = {user_id, timestamp};
    return post("last_seen", columns, 2, values, 2);
}

int mx_post_message(const char *message_id,
                    const char *chat_id,
                    const char *timestamp,
                    const char *send_to_id,
                    const char *send_from_id,
                    const char *message) {
    const char *columns[6] = { "message_id", "chat_id", "timestamp",
                               "send_to_id", "send_from_id", "message"};
    const char *values[6] = {message_id, chat_id, timestamp, send_to_id, send_from_id, message};
    return post("message", columns, 6, values, 6);
}

// і тд. і тп.