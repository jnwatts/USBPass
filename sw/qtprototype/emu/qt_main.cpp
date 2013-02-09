#include <QApplication>
#include <avr/io.h>
#include "avr_emu.h"
#include "mainwindow.h"
#include "time.h"

extern "C" {
void eeprom_init(void);
void eeprom_close(void);
void avr_putch(char c);
}

AVR *avr = NULL;

void avr_halt(void) {
    eeprom_close();
    if (avr) {
        if (avr->isRunning())
            avr->terminate();
        delete avr;
        avr = NULL;
    }
}

void avr_reset(void) {
    avr_halt();
    eeprom_init();
    io_init();
    avr = new AVR();
    avr->start();
}


void avr_putch(char c) {
    avr.
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    avr_reset();
    
    int result = a.exec();

    avr_halt();

    return result;
}
