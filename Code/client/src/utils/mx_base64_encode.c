//
// Created by oleksandra on 24/11/24.
//

#include "utils.h"
#include "libbase64.h"
#include <string.h>

#include <stdlib.h>

int mx_base64_encode(const char *input_str, char **encoded_str) {
    size_t input_size = strlen(input_str);
    size_t encoded_size = ((input_size + 2) / 3) * 4;
    *encoded_str = malloc(encoded_size + 1);

    if (!(*encoded_str)) return -1;

    size_t actual_encoded_size;
    base64_encode(input_str, input_size, *encoded_str, &actual_encoded_size, 0);
    (*encoded_str)[actual_encoded_size] = '\0';

    return 0;
}
