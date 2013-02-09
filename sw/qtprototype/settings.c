#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "settings.h"

#define EEPROM_SETTINGS_ADDR ((void*)(800))

typedef struct {
    Action_t SW1_ACTION;
    Action_t SW1_LONG_ACTION;
    Action_t SW2_ACTION;
    Action_t SW2_LONG_ACTION;
    Action_t SW3_ACTION;
    Action_t SW3_LONG_ACTION;
    uint16_t PASTE_MODE_TIMEOUT;
    uint8_t NUM_KEYS;
    int8_t QUICK_KEY_1;
    int8_t QUICK_KEY_2;
    int8_t QUICK_KEY_3;
} Settings_t;


const Settings_t default_settings PROGMEM = {
    ACTION_PASTE_KEY,
    ACTION_PASTE_QUICK_1,
    ACTION_KEY_UP,
    ACTION_PASTE_QUICK_2,
    ACTION_KEY_DOWN,
    ACTION_PASTE_QUICK_3,
    10*000,
    0,
    -1,
    -1,
    -1
};

void *_settings_get_address(SettingsId_t id, void **addr, int *size);

void settings_restore_defaults(void) {
    eeprom_update_block(&default_settings, EEPROM_SETTINGS_ADDR, sizeof(default_settings));
}

int settings_get_int(SettingsId_t id) {
    void *addr;
    int size;
    int ret = 0;
    _settings_get_address(id, &addr, &size);
    if (size > 0) {
        eeprom_read_block(&ret, addr, size);
    }
    return ret;
}

void settings_set_int(SettingsId_t id, int value) {
    void *addr;
    int size;
    _settings_get_address(id, &addr, &size);
    if (size > 0) {
        eeprom_update_block(&value, addr, size);
    }
}

#define SETTING_OFFSET(setting) case SETTINGS_##setting: *addr += offsetof(Settings_t, setting); *size = sizeof(default_settings.setting); break;
void *_settings_get_address(SettingsId_t id, void **addr, int *size) {
    assert(id < SETTINGS_MAX);
    *addr = (void*)EEPROM_SETTINGS_ADDR;
    *size = 0;
    switch (id) {
    SETTING_OFFSET(SW1_ACTION);
    SETTING_OFFSET(SW1_LONG_ACTION);
    SETTING_OFFSET(SW2_ACTION);
    SETTING_OFFSET(SW2_LONG_ACTION);
    SETTING_OFFSET(SW3_ACTION);
    SETTING_OFFSET(SW3_LONG_ACTION);
    SETTING_OFFSET(PASTE_MODE_TIMEOUT);
    SETTING_OFFSET(NUM_KEYS);
    SETTING_OFFSET(QUICK_KEY_1);
    SETTING_OFFSET(QUICK_KEY_2);
    SETTING_OFFSET(QUICK_KEY_3);
    case SETTINGS_MAX:
        assert(false);
        break;
    }
    return addr;
}
