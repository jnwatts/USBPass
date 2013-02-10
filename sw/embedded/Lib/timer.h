#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

extern unsigned long _time_ms;
extern unsigned int _time_8hz;

void init_timers(void);

inline
unsigned long time(void) {
	return (_time_ms + TCNT1);
}

inline unsigned int time_8hz(void) {
	return (_time_8hz);
}

#endif
