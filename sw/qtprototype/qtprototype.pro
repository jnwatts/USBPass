#-------------------------------------------------
#
# Project created by QtCreator 2013-01-28T20:36:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtprototype
TEMPLATE = app

INCLUDEPATH += \
	$${CWD}/avr \
	$${CWD}/emu

SOURCES += \
    avr/io.c \
    avr/time.cpp \
    emu/mainwindow.cpp \
    emu/avr_emu.cpp \
    emu/qt_main.cpp \
    action.c \
    button.c \
    hid_keyboard.c \
    main.c \
    key_store.c \
    avr/eeprom.c \
    settings.c

HEADERS  += \
    avr/io.h \
    avr/interrupt.h \
    emu/mainwindow.h \
    emu/avr_emu.h \
    pin_map.h \
    button.h \
    util.h \
    action.h \
    settings.h \
    hid_keyboard.h \
    debug.h \
    key_store.h \
    avr/eeprom.h \
    time.hpp \
    avr/pgmspace.h

FORMS    += \
    emu/mainwindow.ui

DEFINES += _GNU_SOURCE

QMAKE_CFLAGS += -std=gnu99
