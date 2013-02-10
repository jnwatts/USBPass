#include <avr/interrupt.h>
#include <avr/io.h>
#include "debug.h"
#include "timer.h"

volatile unsigned int _time_40hz = 0;
volatile unsigned int _time_8hz = 0;
volatile unsigned long _time_ms = 0;

void timer_init(void)
{
	// Reset and hold timers
	GTCCR |= (1<<TSM) | (1<<PSRSYNC);

	// Setup timer1 (source of 8Hz ticks and 1ms resolution time)
	TCCR1A = 0; // WGM1 = 0100b, CS1 = 010b
	TCCR1B = (1<<WGM12) | (1<<CS11); // count to TOP, clk_io/8
	OCR1B = 25000; // Interrupt at 8MHz / 8 / 25000 = 40Hz (25ms)
	OCR1A = 40000; // Interrupt at 8MHz / 8 / 40000 = 25Hz (40ms)
	TIMSK1 = (1<<OCIE1A) | (1<<OCIE1B);

	GTCCR &= ~(TSM);
}

ISR(TIMER1_COMPB_vect)
{
	if (_time_40hz++ > 5) {
		_time_40hz = 0;
		_time_8hz++;
	}
	OCR1B += 25000;
	if (OCR1B >= OCR1A)
		OCR1B -= OCR1A;
}

ISR(TIMER1_COMPA_vect)
{
	_time_ms += 40;
}
