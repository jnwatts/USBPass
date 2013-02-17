#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <avr/eeprom.h>
#include "settings.h"
#include "timer.h"
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

void key_store_init(void)
{
	num_keys = settings_get_int(SETTINGS_NUM_KEYS);
	quick_key[QUICKKEY_1] = settings_get_int(SETTINGS_QUICK_KEY_1);
	quick_key[QUICKKEY_2] = settings_get_int(SETTINGS_QUICK_KEY_2);
	quick_key[QUICKKEY_3] = settings_get_int(SETTINGS_QUICK_KEY_3);

	DBG("num_keys=%d", num_keys);
	DBG("quick_key[1]=%d", quick_key[QUICKKEY_1]);
	DBG("quick_key[2]=%d", quick_key[QUICKKEY_2]);
	DBG("quick_key[3]=%d", quick_key[QUICKKEY_3]);

	if (num_keys > 0)
		current_key_index = 0;
	else
		current_key_index = KEY_STORE_INVALID_INDEX;
}

void key_store_paste(int index) {
    if (index == KEY_STORE_INVALID_INDEX) {
		DBG("Invalid index");
        return;
    }

    eeprom_read_block(
                &current_key.key,
                _key_store_eeprom_addr_from_index(index) + offsetof(Key_t, key),
                sizeof(&current_key.key)
                );

	if (current_key.key[0] != '\0') {
        hid_key_print(&current_key.key[0]);
    }
}

void key_store_paste_name(int index) {
    if (index == KEY_STORE_INVALID_INDEX) {
		DBG("Invalid index");
        return;
    }

    eeprom_read_block(
                &current_key.name,
                _key_store_eeprom_addr_from_index(index) + offsetof(Key_t, name),
                sizeof(&current_key.name)
                );

	if (current_key.name[0] != '\0') {
        hid_key_print(&current_key.name[0]);
	}
}

void key_store_paste_mode(void) {
    paste_mode_end_time = time() + settings_get_int(SETTINGS_PASTE_MODE_TIMEOUT);
}

int key_store_num_keys(void) {
    return num_keys;
}

void key_store_incr(int count) {
	if (count < 0)
		return;
	if (num_keys == 0)
		return;
	if (current_key_index + count >= num_keys)
		current_key_index = num_keys - 1;
	else
		current_key_index += count;
	DBG("current_key_index=%d", current_key_index);
    if (_key_store_is_paste_mode())
        key_store_paste_name(current_key_index);
}

void key_store_decr(int count) {
	if (count < 0)
		return;
	if (num_keys == 0)
		return;
	if (count > current_key_index)
		current_key_index = num_keys - 1;
	else
		current_key_index -= count;
	DBG("current_key_index=%d", current_key_index);
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
    return (time() < paste_mode_end_time);
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
