#ifndef KEY_STORE_H
#define KEY_STORE_H

#define KEY_STORE_MAX_KEYS 20 // 32 bytes per key plus 8 bytes for name, 20*(32+8)=800 bytes. Leaves 224 bytes for settings
#define KEY_STORE_MAX_KEY_LEN 32
#define KEY_STORE_MAX_KEY_NAME_LEN 8

#define KEY_STORE_INVALID_INDEX (-1)

typedef enum {
    QUICKKEY_1 = 0,
    QUICKKEY_2,
    QUICKKEY_3,
    QUICKKEY_MAX
} QuickKey_t;

typedef struct {
    char key[KEY_STORE_MAX_KEY_LEN];
    char name[KEY_STORE_MAX_KEY_NAME_LEN];
} Key_t;

void key_store_init(void);

void key_store_paste(int index);
void key_store_paste_name(int index);
void key_store_paste_mode(void);
int key_store_num_keys(void);
void key_store_incr(int count);
void key_store_decr(int count);
int key_store_index(void);
int key_store_quick_index(QuickKey_t quickkey);

#endif // KEY_STORE_H
