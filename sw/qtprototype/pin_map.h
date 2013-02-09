#ifndef PIN_MAP_H
#define PIN_MAP_H

#include <avr/io.h>

typedef enum {
    BUTTON_SW1,
    BUTTON_SW2,
    BUTTON_SW3,
    BUTTON_MAX
} Button_t;
#define NUM_BUTTONS (BUTTON_MAX)

#define SW1_PORT PORTD
#define SW2_PORT PORTD
#define SW3_PORT PORTD

#define SW1_PIN PORTD0
#define SW2_PIN PORTD1
#define SW3_PIN PORTD2

#endif // PIN_MAP_H
