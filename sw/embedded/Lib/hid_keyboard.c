#include "hid_keyboard.h"

static char string_buffer[HID_KEYBOARD_BUFFER_SIZE] = {'\0'};
static int buffer_pos = 0;

void hid_key_print(const char *str)
{
	//TODO: This needs to be done in a "thread" safe manner, and with a "dma" operation
	strncpy(string_buffer, str, sizeof(string_buffer));
	buffer_pos = 0;
}

void hid_key_print_P(const char *str)
{
	strncpy_P(string_buffer, str, sizeof(string_buffer));
	buffer_pos = 0;
}

char hid_key_get_key(void) {
	if (buffer_pos < sizeof(string_buffer) && string_buffer[buffer_pos] != '\0') {
		DBG("KEY: %c\r\n", string_buffer[buffer_pos]);
		return string_buffer[buffer_pos++];
	} else {
		return '\0';
	}
}
