#ifndef BUTTON_H
#define BUTTON_H

#include <stdlib.h>
#include <stdbool.h>
#include <avr/io.h>
#include "time.hpp"
#include "debug.h"

#define DEFAULT_BUTTON_DEBOUCE_TIME (50) // Milliseconds
#define DEFAULT_BUTTON_LONG_TIME    (1000) // Milliseconds

typedef void (*ButtonCallback)(void *priv);

typedef struct {
    bool active_high;
    unsigned long last_change_time;
    unsigned long debounce_time;
    unsigned long long_press_time;
    bool long_pressed;
    unsigned int previous_value;
    unsigned int *port;
    unsigned int pin;
    ButtonCallback press_cb;
    ButtonCallback release_cb;
    ButtonCallback long_press_cb;
    void *priv;
} button_obj_t;

void button_init(button_obj_t *obj);

static inline
void button_check(button_obj_t *obj) {
    unsigned int value = (*(obj->port) & _BV(obj->pin)) ? 1 : 0;
    unsigned int active = (obj->active_high == (value == 1));
    unsigned long now = avr_time();
    if (value != obj->previous_value) {
        if (now - obj->last_change_time <= obj->debounce_time) {
//            DBG("Change, inside debounce\n");
            return;
        }
        if (active) {
//            DBG("Press, outside debounce\n");
            if (obj->press_cb)
                obj->press_cb(obj->priv);
        } else {
            obj->long_pressed = false;
//            DBG("now - obj->last_change_time <= obj->long_press_time: %ld <= %ld\n", now - obj->last_change_time, obj->long_press_time);
            if (now - obj->last_change_time <= obj->long_press_time || obj->long_press_cb == NULL) {
//                DBG("Short release, outside debounce\n");
                if (obj->release_cb)
                    obj->release_cb(obj->priv);
            }
        }
        obj->last_change_time = now;
        obj->previous_value = value;
    } else if (active && obj->long_press_cb && !obj->long_pressed) {
        if (now - obj->last_change_time > obj->long_press_time) {
            obj->long_pressed = true;
//            DBG("Long press, outside debounce\n");
            if (obj->long_press_cb)
                obj->long_press_cb(obj->priv);
        }

    }
}

#endif // BUTTON_H
