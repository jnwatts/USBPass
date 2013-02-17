#-------------------------------------------------
#
# Project created by QtCreator 2013-02-14T18:18:19
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = usbpass
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -L../hidapi/libusb/.libs -lhidapi-libusb
QMAKE_CXXFLAGS += -I../hidapi/hidapi -ggdb

SOURCES += main.cpp \
    usbpassdevice.cpp

HEADERS += \
    usbpassdevice.h
