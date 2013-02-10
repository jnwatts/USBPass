#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <avr/eeprom.h>
#include "settings.h"
#include "time.h"
#include "key_store.h"
#include "hid_keyboard.h"

static int num_keys = 0;
static int current_key_index = KEY_STORE_INVALID_INDEX;
static int quick_key[QUICKKEY_MAX] = {KEY_STORE_INVALID_INDEX, KEY_STORE_INVALID_INDEX, KEY_STORE_INVALID_INDEX};
static unsigned long paste_mode_end_time = 0;

Key_t current_key;

bool _key_store_is_paste_mode(void);
void _key_store_check_key_index(void);
void *_key_store_eeprom_addr_from_index(int index);

void key_store_paste(int index) {
    if (index == KEY_STORE_INVALID_INDEX) {
        //TODO: Print invalid?
        return;
    }

    eeprom_read_block(
                &current_key.key,
                _key_store_eeprom_addr_from_index(index) + offsetof(Key_t, key),
                sizeof(&current_key.key)
                );

    unsigned int i = 0;
    while (current_key.key[i] != '\0' && i < sizeof(current_key.key)) {
        hid_key_putch_raw(current_key.key[i]);
        i++;
    }
}

void key_store_paste_name(int index) {
    if (index == KEY_STORE_INVALID_INDEX) {
        //TODO: Print invalid?
        return;
    }

    eeprom_read_block(
                &current_key.name,
                _key_store_eeprom_addr_from_index(index) + offsetof(Key_t, name),
                sizeof(&current_key.name)
                );

    unsigned int i = 0;
    while (current_key.name[i] != '\0' && i < sizeof(current_key.name)) {
        hid_key_putch(current_key.name[i]);
        i++;
    }
}

void key_store_paste_mode(void) {
    paste_mode_end_time = avr_time() + settings_get_int(SETTINGS_PASTE_MODE_TIMEOUT);
}

int key_store_num_keys(void) {
    return num_keys;
}

void key_store_incr(int count) {
    current_key_index += count;
    _key_store_check_key_index();
    if (_key_store_is_paste_mode())
        key_store_paste_name(current_key_index);
}

void key_store_decr(int count) {
    current_key_index -= count;
    _key_store_check_key_index();
    if (_key_store_is_paste_mode())
        key_store_paste_name(current_key_index);
}

int key_store_index(void) {
    return current_key_index;
}

int key_store_quick_index(QuickKey_t quickkey) {
    return quick_key[quickkey];
}

bool _key_store_is_paste_mode(void) {
    return (avr_time() < paste_mode_end_time);
}

void _key_store_check_key_index(void) {
    if (current_key_index > key_store_num_keys()) {
        current_key_index = key_store_num_keys() - 1;
    } else if (current_key_index < 0) {
        current_key_index = 0;
    }
}

void *_key_store_eeprom_addr_from_index(int index) {
    assert(index < KEY_STORE_MAX_KEYS);
    return (void*)(sizeof(Key_t) * index);
}
