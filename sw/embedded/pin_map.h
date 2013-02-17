#ifndef PIN_MAP_H
#define PIN_MAP_H

#include <avr/io.h>

typedef enum {
    BUTTON_SW1 = 0x00,
    BUTTON_SW2 = 0x01,
    BUTTON_SW3 = 0x02,
    BUTTON_SW1L = 0x80,
    BUTTON_SW2L = 0x81,
    BUTTON_SW3L = 0x82,
    BUTTON_MAX
} Button_t;
#define NUM_BUTTONS (3)

#define SW1_PORT PIND
#define SW2_PORT PIND
#define SW3_PORT PIND

#define SW1_PIN PORTD4
#define SW2_PIN PORTD5
#define SW3_PIN PORTD6

#endif // PIN_MAP_H
