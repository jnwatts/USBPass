#include <avr/io.h>
#include <avr/interrupt.h>
#include "time.h"
#include "pin_map.h"
#include "action.h"
#include "button.h"
#include "util.h"
#include "settings.h"

#ifdef __x86_64__
#define AVR_MAIN avr_main
#else
#define AVR_MAIN main
#endif

button_obj_t buttons[NUM_BUTTONS];

void setup_hardware(void);

int AVR_MAIN(void)
{
    setup_hardware();

    while (1) {
        button_check(&buttons[BUTTON_SW1]);
        button_check(&buttons[BUTTON_SW2]);
        button_check(&buttons[BUTTON_SW3]);
        delay_ms(1);
    }

    return 0;
}

void setup_hardware(void)
{
    button_obj_t *b = NULL;
    time_init();

    b = &buttons[BUTTON_SW1];
    button_init(b);
    b->port = &SW1_PORT;
    b->pin = SW1_PIN;
    map_button_to_action(b, ACTION_TYPE_SHORT, settings_get_int(SETTINGS_SW1_ACTION));
    map_button_to_action(b, ACTION_TYPE_LONG, settings_get_int(SETTINGS_SW1_LONG_ACTION));

    b = &buttons[BUTTON_SW2];
    button_init(b);
    b->port = &SW2_PORT;
    b->pin = SW2_PIN;
    map_button_to_action(b, ACTION_TYPE_SHORT, settings_get_int(SETTINGS_SW2_ACTION));
    map_button_to_action(b, ACTION_TYPE_LONG, settings_get_int(SETTINGS_SW2_LONG_ACTION));

    b = &buttons[BUTTON_SW3];
    button_init(b);
    b->port = &SW3_PORT;
    b->pin = SW3_PIN;
    map_button_to_action(b, ACTION_TYPE_SHORT, settings_get_int(SETTINGS_SW3_ACTION));
    map_button_to_action(b, ACTION_TYPE_LONG, settings_get_int(SETTINGS_SW3_LONG_ACTION));
}

ISR(PCINT0_vect)
{
}
