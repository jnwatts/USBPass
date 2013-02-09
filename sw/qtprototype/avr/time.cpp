#include <QTime>
#include "time.hpp"

QTime _time;

void time_init() {
    _time.start();
}

unsigned long avr_time(void) {
    return _time.elapsed();
}

void delay_ms(unsigned long delay) {
    usleep(delay * 1000);
}
