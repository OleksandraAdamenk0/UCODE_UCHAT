//
// Created by oleksandra on 04/12/24.
//

#include "client.h"
#include "gui.h"

int mx_close_app() {
    g_object_unref(app);
    return 0;
}
