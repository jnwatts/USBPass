#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/crc16.h>
#include "settings.h"
#include "debug.h"

#define EEPROM_SETTINGS_ADDR ((uint8_t*)(800))

#if 0
#define DEBUG_SETTINGS DBG
#else
#define DEBUG_SETTINGS(fmt, args...) (void)0
#endif

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
	int16_t SETTINGS_CRC;
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
    -1,
	0
};

void *_settings_get_address(SettingsId_t id, void **addr, int *size);
uint16_t _settings_calculate_crc(void);
void _settings_update_crc(void);

void settings_init(void)
{
	uint16_t crc_calc = 0;
	uint16_t crc_read = 0;

	crc_calc = _settings_calculate_crc();
	crc_read = eeprom_read_word(EEPROM_SETTINGS_ADDR + offsetof(Settings_t, SETTINGS_CRC));

	if (crc_calc != crc_read) {
		DBG("Settings CRC failure, loading default settigns\r\n");
		settings_restore_defaults();
	}
}

void settings_restore_defaults(void) {
	int i = 0;
	for (i = 0; i < sizeof(default_settings) -  sizeof(default_settings.SETTINGS_CRC); i++) {
		eeprom_update_byte(EEPROM_SETTINGS_ADDR + i, pgm_read_byte(((uint8_t*)&default_settings) + i));
		DEBUG_SETTINGS("Update 1 bytes to %p: %x, readback: %x\r\n", addr, data);
	}
	_settings_update_crc();
}

int settings_get_int(SettingsId_t id) {
    void *addr;
    int size;
    int ret = 0;
    _settings_get_address(id, &addr, &size);
    if (size > 0) {
        eeprom_read_block(&ret, addr, size);
		DEBUG_SETTINGS("Read %d bytes from %p: %x\r\n", size, addr, ret);
    }
    return ret;
}

void settings_set_int(SettingsId_t id, int value) {
    void *addr;
    int size;
    _settings_get_address(id, &addr, &size);
    if (size > 0) {
        eeprom_update_block(&value, addr, size);
		_settings_update_crc();
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

uint16_t _settings_calculate_crc(void)
{
	uint16_t crc = 1;
	uint8_t data = 0;
	int i = 0;
	for (i = 0; i < sizeof(Settings_t) - sizeof(default_settings.SETTINGS_CRC); i++) {
		data = eeprom_read_byte(EEPROM_SETTINGS_ADDR + i);
		DEBUG_SETTINGS("Read 1 bytes from %p: %x\r\n", EEPROM_SETTINGS_ADDR + i, data);
		crc = _crc16_update(crc, data);
	}
	return crc;
}

void _settings_update_crc(void)
{
	uint16_t crc = _settings_calculate_crc();
	eeprom_update_word(EEPROM_SETTINGS_ADDR + offsetof(Settings_t, SETTINGS_CRC), crc);
}
