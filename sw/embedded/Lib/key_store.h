#ifndef KEY_STORE_H
#define KEY_STORE_H

#define KEY_STORE_MAX_KEYS 20 // 32 bytes per key plus 8 bytes for name, 20*(32+8)=800 bytes. Leaves 224 bytes for settings
#define KEY_STORE_MAX_KEY_LEN 32
#define KEY_STORE_MAX_KEY_NAME_LEN 8

#define KEY_STORE_INVALID_INDEX (-1)

#define KEY_STORE_NUM_QUICK_KEYS 6

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
int key_store_quick_index(int quickkey);

void key_store_set_key(char *buf, int offset, int length);
void key_store_set_name(char *buf, int offset, int length);
void key_store_commit_index(int index);

void key_store_set_num_keys(int count);

void key_store_set_quick_index(int quickkey, int index);

#endif // KEY_STORE_H
