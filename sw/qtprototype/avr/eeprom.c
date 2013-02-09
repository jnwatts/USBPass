#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <avr/eeprom.h>

#define EEPROM_SIZE 1024
static int eeprom_fd = 0;

void eeprom_init(void) {
    if (eeprom_fd == 0) {
        eeprom_fd = open("eeprom.dat", O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
        if (eeprom_fd < 0)
            perror("Failed to open eeprom.dat");
        assert(eeprom_fd > 0);
        lseek(eeprom_fd, EEPROM_SIZE - 1, SEEK_SET);
        lseek(eeprom_fd, 0, SEEK_SET);
    }
}

void eeprom_close(void) {
    if (eeprom_fd > 0) {
        close(eeprom_fd);
        eeprom_fd = 0;
    }
}

#define EEPROM_READWRITE(T, name, def) \
    T eeprom_read_##name(const T *__p) { \
        T ret = def; \
        eeprom_read_block(&ret, __p, sizeof(T)); \
        return ret; \
    } \
    void eeprom_write_##name(T *__p, T __value) { \
        eeprom_write_block(&__value, __p, sizeof(T)); \
    } \
    void eeprom_update_##name(T *__p, T __value) { \
        T cur = eeprom_read_##name(__p); \
        if (cur != __value) { \
            eeprom_write_##name(__p, __value); \
        } \
    }

EEPROM_READWRITE(uint8_t, byte, 0)
EEPROM_READWRITE(uint16_t, word, 0)
EEPROM_READWRITE(uint32_t, dword, 0)
EEPROM_READWRITE(float, float, 0.0f)

void eeprom_read_block (void *__dst, const void *__src, size_t __n) {
    assert((off_t)__src < EEPROM_SIZE);
    lseek(eeprom_fd, (off_t)__src, SEEK_SET);
    read(eeprom_fd, __dst, __n);
}

void eeprom_write_block (const void *__src, void *__dst, size_t __n) {
    assert((off_t)__dst < EEPROM_SIZE);
    lseek(eeprom_fd, (off_t)__dst, SEEK_SET);
    write(eeprom_fd, __src, __n);
    syncfs(eeprom_fd);
}

void eeprom_update_block (const void *__src, void *__dst, size_t __n) {
    while (__n > 0) {
        __n--;
        eeprom_update_byte(__dst++, *(uint8_t*)__src++);
    }
}
