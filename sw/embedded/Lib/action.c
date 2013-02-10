#include "action.h"
#include "key_store.h"

void action_key_up(void *priv) {
    (void)priv;
    key_store_incr(1);
}

void action_key_down(void *priv) {
    (void)priv;
    key_store_decr(1);
}

void action_paste_key(void *priv) {
    (void)priv;
    key_store_paste(key_store_index());
}

void action_paste_mode(void *priv) {
    (void)priv;
    key_store_paste_name(key_store_index());
    key_store_paste_mode();
}

void action_paste_quick_1(void *priv) {
    (void)priv;
    key_store_paste(key_store_quick_index(QUICKKEY_1));
}

void action_paste_quick_2(void *priv) {
    (void)priv;
    key_store_paste(key_store_quick_index(QUICKKEY_2));
}

void action_paste_quick_3(void *priv) {
    (void)priv;
    key_store_paste(key_store_quick_index(QUICKKEY_3));
}



void map_button_to_action(button_obj_t *button, ActionType_t type, Action_t action) {
    ButtonCallback *cb = NULL;
    if (type == ACTION_TYPE_SHORT)
        cb = &button->release_cb;
    else
        cb = &button->long_press_cb;

    switch (action) {
    case ACTION_PASTE_KEY:
        *cb = action_paste_key;
        break;
    case ACTION_PASTE_QUICK_1:
        *cb = action_paste_quick_1;
        break;
    case ACTION_INVALID:
    default:
        *cb = NULL;
        break;
    }
}
