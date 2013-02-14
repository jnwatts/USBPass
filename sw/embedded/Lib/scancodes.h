#ifndef __SCANCODES_H
#define __SCANCODES_H

#include <stdint.h>
#include <stdbool.h>
#include <LUFA/Drivers/USB/USB.h>

bool ascii_to_scancode(char c, uint8_t *code, uint8_t *mod);

#endif
