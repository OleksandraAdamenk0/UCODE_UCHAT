#include "libmx.h"

/**
 * @NAME Print multibyte characters
 * @DESCRIPTION Create a function that outputs ASCII
 * and multibyte characters to the standard output.
 * @note \n
 */
void mx_print_unicode(wchar_t c) {
    char characters[5];
    if (c < 0x80) {
        characters[0] = c;
        write(1, characters, 1);
    } else if (c < 0x800) {
        characters[0] = 0xC0 | (c >> 6);
        characters[1] = 0x80 | (c & 0x3F);
        write(1, characters, 2);
    } else if (c < 0x10000) {
        characters[0] = 0xE0 | (c >> 12);
        characters[1] = 0x80 | ((c >> 6) & 0x3F);
        characters[2] = 0x80 | (c & 0x3F);
        write(1, characters, 3);
    } else if (c < 0x200000) {
        characters[0] = 0xF0 | (c >> 18);
        characters[1] = 0x80 | ((c >> 12) & 0x3F);
        characters[2] = 0x80 | ((c >> 6) & 0x3F);
        characters[3] = 0x80 | (c & 0x3F);
        write(1, characters, 4);
    }
}

