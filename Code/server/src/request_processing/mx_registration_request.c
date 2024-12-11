//
// Created by oleksandra on 12/11/24.
//

#include "request_processing.h"
#include "database.h"
#include "libmx.h"

static const char *valid_country_codes[] = {
        "1", "20", "27", "30", "31", "32", "33", "34", "36", "39",
        "40", "41", "43", "44", "45", "46", "47", "48", "49",
        "51", "52", "53", "54", "55", "56", "57", "58", "60",
        "61", "62", "63", "64", "65", "66", "81", "82", "84",
        "86", "90", "91", "92", "93", "94", "95", "98", "211",
        "212", "213", "216", "218", "220", "221", "222", "223",
        "224", "225", "226", "227", "228", "229", "230", "231",
        "232", "233", "234", "235", "236", "237", "238", "239",
        "240", "241", "242", "243", "244", "245", "246", "247",
        "248", "249", "250", "251", "252", "253", "254", "255",
        "256", "257", "258", "260", "261", "262", "263", "264",
        "265", "266", "267", "268", "269", "290", "291", "297",
        "298", "299", "350", "351", "352", "353", "354", "355",
        "356", "357", "358", "359", "370", "371", "372", "373",
        "374", "375", "376", "377", "378", "379", "380", "381",
        "382", "383", "385", "386", "387", "389", "420", "421",
        "423", "500", "501", "502", "503", "504", "505", "506",
        "507", "508", "509", "590", "591", "592", "593", "594",
        "595", "596", "597", "598", "599", "670", "672", "673",
        "674", "675", "676", "677", "678", "679", "680", "681",
        "682", "683", "685", "686", "687", "688", "689", "690",
        "691", "692", "850", "852", "853", "855", "856", "880",
        "886", "960", "961", "962", "963", "964", "965", "966",
        "967", "968", "970", "971", "972", "973", "974", "975",
        "976", "977", "992", "993", "994", "995", "996", "998",
        NULL
};

static int validate_password(const char *password) {
    if (mx_strlen(password) < 8) return -1;
    //            {upper,        lower,     digit,     symbol}
    bool req[4] = {false, false, false, false};
    const char *symbols = "!@#$*-_?.";

    for (int i = 0; i < mx_strlen(password); ++i) {
        if (password[i] >= 'A' && password[i] <= 'Z') req[0] = true;
        else if (password[i] >= 'a' && password[i] <= 'z') req[1] = true;
        else if (password[i] >= '0' && password[i] <= '9') req[2] = true;
        else if (mx_get_char_index(symbols, password[i]) >= 0) req[3] = true;
        else return -1;
    }

    for (int i = 0; i < 4; ++i) if (!req[i]) return -1;
    return 0;
}

static int validate_email(const char *email) {
    // check @
    int at_amount = mx_count_substr(email, "@");
    if (at_amount != 1 || email[0] == '@') return -1;

    char **email_parts = mx_strsplit(email, '@');
    if (!email_parts || !email_parts[0]) return -1;

    // check . in domen
    int dot_index = mx_get_char_index(email_parts[1], '.');
    if (dot_index < 1 || dot_index == mx_strlen(email_parts[1]) - 1) {
        free(email_parts[0]);
        free(email_parts[1]);
        free(email_parts);
        return -1;
    }

    // check invalid symbols?
    // I don't feel like it )))))))
    return 0;
}

static char *sanitize_number(const char *phone) {
    // get length
    int new_len = 0;
    for (int i = 0; i < mx_strlen(phone); ++i)
        if (!(phone[i] == ' ' || phone[i] == '-')) new_len++;
    if (new_len == 0) return NULL;

    // sanitize
    char *result = mx_strnew(new_len);
    int counter = 0;
    for (int i = 0; i < mx_strlen(phone); ++i)
        if (!(phone[i] == ' ' || phone[i] == '-')) result[counter++] = phone[i];

    return result;
}

static int validate_phone(const char *phone) {
    // get rid of '-' and ' '
    char *sanitized_phone = sanitize_number(phone);
    if (sanitized_phone == NULL) {
        free(sanitized_phone);
        return -1;
    }

    // check if sanitized string contains only digits
    if (!mx_is_numeric(sanitized_phone)) {
        free(sanitized_phone);
        return -1;
    }

    // check length
    if (mx_strlen(sanitized_phone) < 10 || mx_strlen(sanitized_phone) > 15) {
        free(sanitized_phone);
        return -1;
    }

    // check country code (INEFFICIENT WAY)
    bool is_code_valid = false;

    for (int i = 0; valid_country_codes[i] != NULL ; ++i) {
        if (mx_strncmp(sanitized_phone,
                       valid_country_codes[i],
                       mx_strlen(valid_country_codes[i])) == 0) {
            is_code_valid = true;
            break;
        }
    }
    if (!is_code_valid) {
        free(sanitized_phone);
        return -1;
    }

    free(sanitized_phone);
    return 0;
}

int mx_registration_request(const cJSON *request) {
    cJSON *username = cJSON_GetObjectItemCaseSensitive(request, "username");
    cJSON *password = cJSON_GetObjectItemCaseSensitive(request, "password");

    // check required fields
    // return values are assigned according to API Documentation
    if (!cJSON_IsString(username) || username->valuestring == NULL ||
    mx_strlen(username->valuestring) == 0) {
        return -1;
    }
    else
    {
        printf("Username: %s\n", username->valuestring);
    }
    
    if (!cJSON_IsString(password) || password->valuestring == NULL ||
          validate_password(password->valuestring) < 0) {
        return -3;
    }
//
   // check if username already exists in DB, if so do not proceed further
   int result = mx_get_user_id(username->valuestring, USERNAME);
   if (result == -2)  return -9;
   if (result > 0) return -2;

   // check existence of email or phone
   cJSON *email = cJSON_GetObjectItemCaseSensitive(request, "email");
   cJSON *phone = cJSON_GetObjectItemCaseSensitive(request, "phone");

   if (!cJSON_IsString(email) || email->valuestring == NULL ||
       mx_strlen(email->valuestring) == 0)
       email = NULL;
   if (!cJSON_IsString(phone) || phone->valuestring == NULL ||
       mx_strlen(phone->valuestring) == 0)
       phone = NULL;
   if (!email && !phone) return -4;

//    // check email format
   if (email) {
       if (validate_email(email->valuestring) < 0) return -6;
       // check if email already was registered in app (check DB)
       result = mx_get_user_id(email->valuestring, EMAIL);
       if (result == -2)  return -9;
       if (result > 0) return -7;
   }

   if (phone) {
       if (validate_phone(phone->valuestring) < 0) return -5;
       result = mx_get_user_id(phone->valuestring, PHONE);
       if (result == -2)  return -9;
       if (result > 0) return -8;
   }
    return 0;
}
