#ifndef AVR_IO_H
#define AVR_IO_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

void io_init(void);

extern unsigned int *portd_addr;

#define PORTD (*portd_addr)

#define PORTD0 0
#define PORTD1 1
#define PORTD2 2

#define _BV(x) (1<<(x))

#ifdef __cplusplus
}
#endif
#endif // AVR_IO_H
