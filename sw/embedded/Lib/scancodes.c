#include "scancodes.h"

typedef struct scancode_table_t {
	char lcase;
	char ucase;
	uint8_t scancode;
} scancode_table_t;

scancode_table_t scancode_table[] = {
	{'a',	'A',	0x04},
	{'b',	'B',	0x05},
	{'c',	'C',	0x06},
	{'d',	'D',	0x07},
	{'e',	'E',	0x08},
	{'f',	'F',	0x09},
	{'g',	'G',	0x0A},
	{'h',	'H',	0x0B},
	{'i',	'I',	0x0C},
	{'j',	'J',	0x0D},
	{'k',	'K',	0x0E},
	{'l',	'L',	0x0F},
	{'m',	'M',	0x10},
	{'n',	'N',	0x11},
	{'o',	'O',	0x12},
	{'p',	'P',	0x13},
	{'q',	'Q',	0x14},
	{'r',	'R',	0x15},
	{'s',	'S',	0x16},
	{'t',	'T',	0x17},
	{'u',	'U',	0x18},
	{'v',	'V',	0x19},
	{'w',	'W',	0x1A},
	{'x',	'X',	0x1B},
	{'y',	'Y',	0x1C},
	{'z',	'Z',	0x1D},
	{'1',	'!',	0x1E},
	{'2',	'@',	0x1F},
	{'3',	'#',	0x20},
	{'4',	'$',	0x21},
	{'5',	'%',	0x22},
	{'6',	'^',	0x23},
	{'7',	'&',	0x24},
	{'8',	'*',	0x25},
	{'9',	'(',	0x26},
	{'0',	')',	0x27},
	{' ',	' ',	0x2C},
	{'-',	'_',	0x2D},
	{'=',	'+',	0x2E},
	{'[',	'{',	0x2F},
	{']',	'}',	0x30},
	{'\\',	'|',	0x31},
	//{'NON_US_HASHMARK',	'TILDE',	0x32},
	{';',	':',	0x33},
	{'\'',	'"',	0x34},
	{'`',	'~',	0x35},
	{',',	'<',	0x36},
	{'.',	'>',	0x37},
	{'/',	'?',	0x38},
};

#define NUM_SCANCODES (sizeof(scancode_table)/sizeof(*scancode_table))

bool ascii_to_scancode(char c, uint8_t *code, uint8_t *mod) {
	int i = 0;
	for (i = 0; i < NUM_SCANCODES; i++) {
		if (c == scancode_table[i].lcase) {
			*code = scancode_table[i].scancode;
			*mod = 0;
			return true;
		} else if (c == scancode_table[i].ucase) {
			*code = scancode_table[i].scancode;
			*mod = HID_KEYBOARD_MODIFIER_LEFTSHIFT; // TODO: Make this configurable?
			return true;
		}
	}

	return false;
}
