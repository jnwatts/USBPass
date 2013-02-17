#ifndef HID_KEYBOARD_H
#define HID_KEYBOARD_H

#include <avr/pgmspace.h>
#include <string.h>
#include <stdbool.h>
#include "debug.h"

#define HID_KEYBOARD_BUFFER_SIZE 64
#define HID_KEYBOARD_ERASE (0x7F)

void hid_key_print(const char *str);
void hid_key_print_P(const char *str);
void hid_key_print_n(const char *str, int len);
char hid_key_peek_key(void);
char hid_key_get_key(void);
void hid_key_consume(void);

#endif // HID_KEYBOARD_H
