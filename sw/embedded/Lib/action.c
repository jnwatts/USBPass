#include "action.h"
#include "key_store.h"
#include "debug.h"

#if 1
#define DEBUG_ACTION DBG
#else
#define DEBUG_ACTION(fmt, args...) (void)0
#endif

void action_key_up(void *priv) {
    (void)priv;
	DEBUG_ACTION("%s\r\n", __func__);
    key_store_incr(1);
}

void action_key_down(void *priv) {
    (void)priv;
	DEBUG_ACTION("%s\r\n", __func__);
    key_store_decr(1);
}

void action_paste_key(void *priv) {
    (void)priv;
	DEBUG_ACTION("%s\r\n", __func__);
    key_store_paste(key_store_index());
}

void action_paste_mode(void *priv) {
    (void)priv;
	DEBUG_ACTION("%s\r\n", __func__);
    key_store_paste_name(key_store_index());
    key_store_paste_mode();
}

void action_paste_quick_1(void *priv) {
    (void)priv;
	DEBUG_ACTION("%s\r\n", __func__);
    key_store_paste(key_store_quick_index(QUICKKEY_1));
}

void action_paste_quick_2(void *priv) {
    (void)priv;
	DEBUG_ACTION("%s\r\n", __func__);
    key_store_paste(key_store_quick_index(QUICKKEY_2));
}

void action_paste_quick_3(void *priv) {
    (void)priv;
	DEBUG_ACTION("%s\r\n", __func__);
    key_store_paste(key_store_quick_index(QUICKKEY_3));
}



void map_button_to_action(button_obj_t *button, ActionType_t type, Action_t action) {
    ButtonCallback *cb = NULL;
    if (type == ACTION_TYPE_SHORT)
        cb = &button->release_cb;
    else
        cb = &button->long_press_cb;

	DEBUG_ACTION("Map %d.%S to %d\r\n", button->pin, (type==ACTION_TYPE_SHORT?PSTR("short"):PSTR("long")), (int)action);

	switch (action) {
		case ACTION_KEY_UP:
			*cb = action_key_up;
			break;
		case ACTION_KEY_DOWN:
			*cb = action_key_down;
			break;
		case ACTION_PASTE_KEY:
			*cb = action_paste_key;
			break;
		case ACTION_PASTE_MODE:
			*cb = action_paste_mode;
			break;
		case ACTION_PASTE_QUICK_1:
			*cb = action_paste_quick_1;
			break;
		case ACTION_PASTE_QUICK_2:
			*cb = action_paste_quick_2;
			break;
		case ACTION_PASTE_QUICK_3:
			*cb = action_paste_quick_3;
			break;

		case ACTION_INVALID:
		default:
			*cb = NULL;
			break;
	}
}
