#ifndef HID_KEYBOARD_H
#define HID_KEYBOARD_H

#define HID_KEYBOARD_BUFFER_SIZE 64
#define HID_KEYBOARD_ERASE (0x7F)

void hid_key_print(const char *str);
void hid_key_putch(char c);
void hid_key_clear(void);
void hid_key_print_raw(const char *str);
void hid_key_putch_raw(char c);

#endif // HID_KEYBOARD_H
