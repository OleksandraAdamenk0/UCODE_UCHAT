#include "libmx.h"

int mx_numlen(int number) {
    if (number == 0) return 1;
    long long int n = (long long int) number;
    n = (n < 0)? -n: n;
    int len = 0;
    for (; n; len++) n /= 10;
    return len;
}
