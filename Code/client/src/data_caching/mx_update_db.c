#include "data_caching.h"

int mx_update_db() {
    int status;
    // get user settings by extern variable id

    // get user contacts by extern variable id
    if ((status = mx_update_contacts()) < 0) return status;

    // get user chats by extern variable id
    if ((status = mx_update_chats()) < 0) return status;
    // for each chat get last 50 messages

    return 0;
}
