#ifndef ACTION_H
#define ACTION_H
#include "button.h"

typedef enum {
    ACTION_INVALID,
    ACTION_KEY_UP,
    ACTION_KEY_DOWN,
    ACTION_PASTE_KEY,
    ACTION_PASTE_MODE,
    ACTION_PASTE_QUICK_1,
    ACTION_PASTE_QUICK_2,
    ACTION_PASTE_QUICK_3,
    ACTION_PASTE_QUICK_4,
    ACTION_PASTE_QUICK_5,
    ACTION_PASTE_QUICK_6,
    ACTION_MAX
} Action_t;

typedef enum {
    ACTION_TYPE_SHORT,
    ACTION_TYPE_LONG,
    ACTION_TYPE_MAX
} ActionType_t;

void map_button_to_action(button_obj_t *button, ActionType_t type, Action_t action);

#endif // ACTION_H
