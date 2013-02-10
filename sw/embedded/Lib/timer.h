#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

extern volatile unsigned long _time_ms;
extern volatile unsigned int _time_8hz;

void timer_init(void);

inline
unsigned long time(void) {
	uint8_t L, H;
	L = TCNT1L;
	H = TCNT1H;
#if 0
	return (_time_ms + ((unsigned long)L + ((unsigned long)H)<<8)/1000);
#else
	return _time_ms;
#endif
}

inline unsigned int time_8hz(void) {
	return (_time_8hz);
}

#endif
