#include <avr/interrupt.h>
#include <avr/io.h>
#include "timer.h"

unsigned int _time_40hz = 0;
unsigned int _time_8hz = 0;
unsigned long _time_ms = 0;

void init_timers(void)
{
	// Reset and hold timers
	GTCCR |= TSM | PSRSYNC;

	// Setup timer1 (source of 8Hz ticks and 1ms resolution time)
	TCCR1A = 0; // WGM1 = 0100b, CS1 = 010b
	TCCR1B = WGM12 | CS11; // CTC mode, count to OCR1A, clk_io/8
	OCR1A = 25000; // CTC interrupt and reset at 8MHz / 8 / 25000 = 40Hz (25ms)
	OCR1B = 40000; // CTC interrupt and reset at 8MHz / 8 / 40000 = 25Hz (40ms)
	TIMSK1 = OCIE1A | OCIE1B;

	GTCCR &= ~(TSM);
}

ISR(TIMER1_COMPA_vect)
{
	if (_time_40hz++ > 5) {
		_time_40hz = 0;
		_time_8hz++;
	}
	OCR1A += 25000;
	if (OCR1A > OCR1B)
		OCR1A -= OCR1B;
}

ISR(TIMER1_COMPB_vect)
{
	_time_ms += 40;
	TCNT1 = 0;
}
