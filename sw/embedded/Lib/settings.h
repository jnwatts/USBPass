#ifndef SETTINGS_H
#define SETTINGS_H

#include "action.h"

typedef enum {
    SETTINGS_SW1_ACTION,
    SETTINGS_SW1_LONG_ACTION,
    SETTINGS_SW2_ACTION,
    SETTINGS_SW2_LONG_ACTION,
    SETTINGS_SW3_ACTION,
    SETTINGS_SW3_LONG_ACTION,
    SETTINGS_PASTE_MODE_TIMEOUT,
    SETTINGS_NUM_KEYS,
    SETTINGS_QUICK_KEY_1,
    SETTINGS_QUICK_KEY_2,
    SETTINGS_QUICK_KEY_3,
    SETTINGS_QUICK_KEY_4,
    SETTINGS_QUICK_KEY_5,
    SETTINGS_QUICK_KEY_6,
    SETTINGS_MAX
} SettingsId_t;

void settings_init(void);
void settings_restore_defaults(void);
int settings_get_int(SettingsId_t id);
void settings_set_int(SettingsId_t id, int value);

#endif // SETTINGS_H
