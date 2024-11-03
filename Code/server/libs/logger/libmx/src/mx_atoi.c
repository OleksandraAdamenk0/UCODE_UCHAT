#include "libmx.h"

int mx_atoi(const char* str) {
    if (!str) return 0;
    int n = 0;
    int sign = (*str == '-')? -1: 1;
    if (*str == '-' || *str == '+') str++;
    while(*str && *str >= '0' && *str <= '9') n = n * 10 + (*str++ - '0');
    return n * sign;
}
