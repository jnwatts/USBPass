#include "hid_keyboard.h"

static char string_buffer[HID_KEYBOARD_BUFFER_SIZE+1] = {'\0'};
static int buffer_pos = -1;

void hid_key_print(const char *str)
{
	//TODO: This needs to be done in a "thread" safe manner, and with a "dma" operation
	strncpy(string_buffer, str, sizeof(string_buffer));
	string_buffer[sizeof(string_buffer)-1] = '\0';
	buffer_pos = 0;
}

void hid_key_print_P(const char *str)
{
	strncpy_P(string_buffer, str, sizeof(string_buffer));
	string_buffer[sizeof(string_buffer)-1] = '\0';
	buffer_pos = 0;
}

void hid_key_print_n(const char *str, int len)
{
	if (len > sizeof(string_buffer) - 1)
		len = sizeof(string_buffer) - 1;
	strncpy(string_buffer, str, len);
	string_buffer[len] = '\0';
	buffer_pos = 0;
}

char hid_key_peek_key(void)
{
	if (buffer_pos >= 0 && buffer_pos < sizeof(string_buffer)) {
		return string_buffer[buffer_pos];
	} else {
		return '\0';
	}
}

char hid_key_get_key(void)
{
	 char c = hid_key_peek_key();
	 DBG("KEY: %c\r\n", string_buffer[buffer_pos]);
	 hid_key_consume();
}

void hid_key_consume(void)
{
	if (buffer_pos < sizeof(string_buffer) && string_buffer[buffer_pos] != '\0') {
		buffer_pos++;
	}
}
