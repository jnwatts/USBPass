#include "button.h"

void button_init(button_obj_t *obj) {
   obj->active_high = true;
   obj->last_change_time = 0;
   obj->debounce_time = DEFAULT_BUTTON_DEBOUCE_TIME;
   obj->long_press_time = DEFAULT_BUTTON_LONG_TIME;
   obj->previous_value = 0;
   obj->port = NULL;
   obj->pin = 0;
   obj->press_cb = NULL;
   obj->release_cb = NULL;
   obj->long_press_cb = NULL;
   obj->priv = NULL;
}

