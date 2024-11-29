//
// Created by oleksandra on 24/11/24.
//

#include "request_processing.h"
#include "libbase64.h"
#include "libmx.h"

int mx_base64_decode(const char *encoded_str, char **decoded_str) {
    size_t encoded_size = mx_strlen(encoded_str);
    size_t decoded_size = (encoded_size / 4) * 3;
    *decoded_str = mx_strnew(decoded_size + 1);

    if (!(*decoded_str)) return -1;

    size_t actual_decoded_size;
    if (base64_decode(encoded_str, encoded_size,
                      *decoded_str, &actual_decoded_size, 0) != 1) {
        free(*decoded_str);
        return -2;
    }

    return actual_decoded_size;
}
