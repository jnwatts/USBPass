#include <avr/io.h>
#include <avr/interrupt.h>
#include "avr_emu.h"
#include "debug.h"

extern "C" {
    int avr_main(void);
}

unsigned int *portd_addr = NULL;

unsigned int AVR::portd = 0;

AVR::AVR(QObject *parent) :
    QThread(parent)
{
    portd_addr = &AVR::portd;
    DBG("portd_addr: %p\n", portd_addr);
}


void AVR::run()
{
    avr_main();
}

void AVR::PCINT0_vect()
{
    ::PCINT0_vect();
}
