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
static int quick_key[KEY_STORE_NUM_QUICK_KEYS] = {KEY_STORE_INVALID_INDEX, KEY_STORE_INVALID_INDEX, KEY_STORE_INVALID_INDEX};
static unsigned long paste_mode_end_time = 0;

Key_t current_key;

bool _key_store_is_paste_mode(void);
void _key_store_check_key_index(void);
void *_key_store_eeprom_addr_from_index(int index);

void key_store_init(void)
{
	num_keys = settings_get_int(SETTINGS_NUM_KEYS);

	quick_key[0] = settings_get_int(SETTINGS_QUICK_KEY_1);
	quick_key[1] = settings_get_int(SETTINGS_QUICK_KEY_2);
	quick_key[2] = settings_get_int(SETTINGS_QUICK_KEY_3);
	quick_key[3] = settings_get_int(SETTINGS_QUICK_KEY_4);
	quick_key[4] = settings_get_int(SETTINGS_QUICK_KEY_5);
	quick_key[5] = settings_get_int(SETTINGS_QUICK_KEY_6);

	DBG("num_keys=%d", num_keys);
	DBG("quick_key[0]=%d", quick_key[0]);
	DBG("quick_key[1]=%d", quick_key[1]);
	DBG("quick_key[2]=%d", quick_key[2]);
	DBG("quick_key[3]=%d", quick_key[3]);
	DBG("quick_key[4]=%d", quick_key[4]);
	DBG("quick_key[5]=%d", quick_key[5]);

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
                sizeof(current_key.key)
                );

	if (current_key.key[0] != '\0') {
        hid_key_print_n(&current_key.key[0], sizeof(current_key.key));
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
                sizeof(current_key.name)
                );

	if (current_key.name[0] != '\0') {
        hid_key_print_n(&current_key.name[0], sizeof(current_key.name));
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

int key_store_quick_index(int quickkey) {
	if (quickkey < KEY_STORE_NUM_QUICK_KEYS)
		return quick_key[quickkey];
	else
		return KEY_STORE_INVALID_INDEX;
}

void key_store_set_key(char *buf, int offset, int length) {
	DBG("offset=%d, length=%d", offset, length);
	if (offset + length >= sizeof(current_key.key))
		return;
#ifdef DEBUG
	int i = 0;
	printf("buf={");
	for (i = 0; i < length; i++) {
		printf("%02x", buf[i]);
	}
	printf("}\r\n");
#endif
	strncpy(current_key.key + offset, buf, length);
	if (offset + length < sizeof(current_key.key))
		current_key.key[offset+length] = '\0';
	DBG();
}

void key_store_set_name(char *buf, int offset, int length) {
	DBG("offset=%d, length=%d", offset, length);
	if (offset + length >= sizeof(current_key.name))
		return;
#ifdef DEBUG
	int i = 0;
	printf("buf={");
	for (i = 0; i < length; i++) {
		printf("%02x", buf[i]);
	}
	printf("}\r\n");
#endif
	strncpy(current_key.name + offset, buf, length);
	if (offset + length < sizeof(current_key.name))
		current_key.name[offset+length] = '\0';
	DBG();
}

void key_store_commit_index(int index) {
	if (index >= num_keys || index < 0)
		return;
	int len = 0;

	len = strnlen(current_key.name, sizeof(current_key.name));
	if (len < sizeof(current_key.name))
		current_key.name[len++] = '\0';
    eeprom_update_block(
                &current_key.name,
                _key_store_eeprom_addr_from_index(index) + offsetof(Key_t, name),
                len
                );
	len = strnlen(current_key.key, sizeof(current_key.key));
	if (len < sizeof(current_key.key))
		current_key.key[len++] = '\0';
    eeprom_update_block(
                &current_key.key,
                _key_store_eeprom_addr_from_index(index) + offsetof(Key_t, key),
                len
                );
	DBG();
}

void key_store_set_num_keys(int count) {
	if (count > KEY_STORE_MAX_KEYS)
		return;
	num_keys = count;
	settings_set_int(SETTINGS_NUM_KEYS, count);
}

void key_store_set_quick_index(int quickkey, int index) {
	SettingsId_t setting_id;
	if (quickkey < 0 || quickkey >= KEY_STORE_NUM_QUICK_KEYS)
		return;
	if (index >= num_keys && index != KEY_STORE_INVALID_INDEX)
		return;
	switch (quickkey) {
		case 0:
			setting_id = SETTINGS_QUICK_KEY_1;
			break;
		case 1:
			setting_id = SETTINGS_QUICK_KEY_2;
			break;
		case 2:
			setting_id = SETTINGS_QUICK_KEY_3;
			break;
		case 3:
			setting_id = SETTINGS_QUICK_KEY_4;
			break;
		case 4:
			setting_id = SETTINGS_QUICK_KEY_5;
			break;
		case 5:
			setting_id = SETTINGS_QUICK_KEY_6;
			break;
		default:
			return;
	}
	quick_key[quickkey] = index;
	settings_set_int(setting_id, index);
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
