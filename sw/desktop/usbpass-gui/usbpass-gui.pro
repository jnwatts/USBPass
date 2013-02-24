#-------------------------------------------------
#
# Project created by QtCreator 2013-02-21T00:02:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = usbpass-gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -ggdb

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += usbpass
}
