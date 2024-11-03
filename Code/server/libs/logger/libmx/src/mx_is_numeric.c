//
// Created by aleksa on 11/2/24.
//
#include "libmx.h"

bool mx_is_numeric(const char *str) {
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] < '0' || str[i] > '9') return 0;
    return 1;
}
