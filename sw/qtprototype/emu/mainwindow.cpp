#include <avr/io.h>
#include <avr/interrupt.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pin_map.h"

#include "avr_emu.h"
#include "debug.h"

extern "C" {
#include "settings.h"
}

extern AVR *avr;

void avr_reset(void);
void avr_halt(void);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pSW1, SIGNAL(pressed()), this, SLOT(button_pressed()));
    connect(ui->pSW1, SIGNAL(released()), this, SLOT(button_released()));
    connect(ui->pSW2, SIGNAL(pressed()), this, SLOT(button_pressed()));
    connect(ui->pSW2, SIGNAL(released()), this, SLOT(button_released()));
    connect(ui->pSW3, SIGNAL(pressed()), this, SLOT(button_released()));
    connect(ui->pSW3, SIGNAL(released()), this, SLOT(button_pressed()));

    button_map[ui->pSW1] = BUTTON_SW1;
    button_map[ui->pSW2] = BUTTON_SW2;
    button_map[ui->pSW3] = BUTTON_SW3;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::button_pressed()
{
    Button_t button = button_map[QObject::sender()];

    switch (button) {
    case BUTTON_SW1:
        SW1_PORT |= _BV(SW1_PIN);
        break;
    case BUTTON_SW2:
        SW2_PORT |= _BV(SW2_PIN);
        break;
    case BUTTON_SW3:
        SW3_PORT |= _BV(SW3_PIN);
        break;
    default:
        break;
    }

    QMetaObject::invokeMethod(avr, "PCINT0_vect", Qt::QueuedConnection);
}

void MainWindow::button_released()
{
    Button_t button = button_map[QObject::sender()];

    switch (button) {
    case BUTTON_SW1:
        SW1_PORT &= ~_BV(SW1_PIN);
        break;
    case BUTTON_SW2:
        SW2_PORT &= ~_BV(SW2_PIN);
        break;
    case BUTTON_SW3:
        SW3_PORT &= ~_BV(SW3_PIN);
        break;
    default:
        break;
    }

    QMetaObject::invokeMethod(avr, "PCINT0_vect", Qt::QueuedConnection);
}

void MainWindow::on_pRESET_clicked()
{
    avr_reset();
}

void MainWindow::on_pRESET_2_clicked()
{
    settings_restore_defaults();
}
