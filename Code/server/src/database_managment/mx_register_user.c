#include "server.h"
#include "database_managment.h"

static int validate_password(const char *password) {
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
    int length = 0;
    char special[] = {'!','@','#','$','*','-','_','?','.'};
    for (int i = 0; password[i] != '\0'; i++) {
        if (password[i] >= 'A' && password[i] <= 'Z') has_upper = 1;
        else if (password[i] >= 'a' && password[i] <= 'z') has_lower = 1;
        else if (password[i] >= '0' && password[i] <= '9') has_digit = 1;
        for (int j = 0; j < 9; j++) { 
            if (password[i] == special[j]) has_special = 1;
        }
        length++;
    }
    if (length < 8) return 0; 

    return has_upper && has_lower && has_digit && has_special;    
}

static int validate_number(const char *phone_number) {
    if (phone_number[0] != '+' || mx_strlen(phone_number) > 15) return 0;
    return 1;
}

int mx_register_user(t_registration *data) {
    sqlite3_stmt *stmt;
    char *sql = "INSERT INTO users (username, password, email, phone, photo) VALUES (?, ?, ?, ?, ?)";

    //validation
    if (!validate_password(data->password)) {
        fprintf(stderr, "Password does not meet criteria.\n");
        return -3;
    }
    if (mx_strcmp(data->email, "") == 0 && mx_strcmp(data->phone, "") == 0) {
        fprintf(stderr, "Either email or phone must be provided.\n");
        return -4;
    }
    if (!validate_number(data->phone)) {
        fprintf(stderr, "Invalid phone format.\n");
        return -5;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return -9;
    }
    printf("data:\nname: %s\npasswort: %s\nemail: %s\nphone: %s\nphoto: %s\n",data->username, data->password, data->email, data->phone, data->photo);

    // Bind username
    if (sqlite3_bind_text(stmt, 1, data->username, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return -9;
    }

    // Bind password
    if (sqlite3_bind_text(stmt, 2, data->password, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return -9;
    }

    // Bind email
    if (data->email) {
        if (sqlite3_bind_text(stmt, 3, data->email, -1, SQLITE_STATIC) != SQLITE_OK) {
            sqlite3_finalize(stmt);
            return -9;
        }
    } else {
        if (sqlite3_bind_null(stmt, 3) != SQLITE_OK) {
            fprintf(stderr, "Error binding NULL email: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            return -9;
        }
    }

    // Bind phone
    if (data->phone) {
        if (sqlite3_bind_text(stmt, 4, data->phone, -1, SQLITE_STATIC) != SQLITE_OK) {
            fprintf(stderr, "Error binding phone: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            return -9;
        }
    } else {
        if (sqlite3_bind_null(stmt, 4) != SQLITE_OK) {
            fprintf(stderr, "Error binding NULL phone: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            return -9;
        }
    }

    // Bind photo
    if (data->photo) {
        if (sqlite3_bind_blob(stmt, 5, data->photo, data->photo_size, SQLITE_STATIC) != SQLITE_OK) {
            fprintf(stderr, "Error binding photo: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            return -9;
        }
    } else {
        if (sqlite3_bind_null(stmt, 5) != SQLITE_OK) {
            fprintf(stderr, "Error binding NULL photo: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            return -9;
        }
    }

    const char *expanded_sql = sqlite3_expanded_sql(stmt);
    if (expanded_sql) {
        printf("Expanded SQL: %s\n", expanded_sql);
        sqlite3_free((void *)expanded_sql);
    } else {
        fprintf(stderr, "Failed to get expanded SQL: %s\n", sqlite3_errmsg(db));
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        const char *error_msg = sqlite3_errmsg(db);
        fprintf(stderr, "SQLite error: %s\n", error_msg);

        if (mx_strcmp(UNIQUE_USERNAME, sqlite3_errmsg(db)) == 0) return -2;
        else if (mx_strcmp(UNIQUE_EMAIL, sqlite3_errmsg(db)) == 0) return -7;
        else if (mx_strcmp(UNIQUE_PHONE, sqlite3_errmsg(db)) == 0) return -8;
        else return -9;
    }

    sqlite3_finalize(stmt);
    return 0;
}
