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

unix {
    CONFIG   += link_pkgconfig
    PKGCONFIG += hidapi-libusb
    PKGCONFIG += usbpass
}

QMAKE_CXXFLAGS += -ggdb

SOURCES += main.cpp

HEADERS +=

