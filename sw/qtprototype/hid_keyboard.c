#ifdef __x86_64__
#include <stdio.h>
#endif
#include "hid_keyboard.h"

static char string_buffer[HID_KEYBOARD_BUFFER_SIZE];
static int buffer_pos = 0;

void hid_key_print(const char *str) {
    while (*str != '\0')
        hid_key_putch(*str++);
}

void hid_key_putch(char c) {
    if (c == HID_KEYBOARD_ERASE) {
        if (buffer_pos > 0) {
            buffer_pos--;
            hid_key_putch_raw(c);
        }
    } else if (buffer_pos < HID_KEYBOARD_BUFFER_SIZE) {
        string_buffer[buffer_pos++] = c;
        hid_key_putch_raw(c);
    }
}

void hid_key_clear(void) {
    while (buffer_pos > 0) {
        hid_key_putch(HID_KEYBOARD_ERASE);
    }
}

void hid_key_print_raw(const char *str) {
    while (*str != '\0')
        hid_key_putch_raw(*str++);
}

void hid_key_putch_raw(char c) {
#ifdef __x86_64__
    putchar(c);
    fflush(stdout);
#endif
}
