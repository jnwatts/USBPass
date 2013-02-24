#-------------------------------------------------
#
# Project created by QtCreator 2013-02-20T23:34:38
#
#-------------------------------------------------

QT       -= gui

TARGET = usbpass
TEMPLATE = lib

DEFINES += LIBUSBPASS_LIBRARY

SOURCES += \
    usbpassdevice.cpp \
    usbpass_private.cpp

HEADERS +=\
    usbpassdevice.h \
    usbpass_private.h

unix {
    CONFIG      += create_pc create_prl no_install_prl
    CONFIG      += link_pkgconfig
    PKGCONFIG   += hidapi-libusb

    prefix = /usr
    target.path = $$prefix/lib
    headers.path = $$prefix/include
    headers.files = usbpassdevice.h

    QMAKE_PKGCONFIG_NAME = usbpass
    QMAKE_PKGCONFIG_DESCRIPTION = Library for communicating with USBPass key-store devices
    QMAKE_PKGCONFIG_PREFIX = $$prefix
    QMAKE_PKGCONFIG_LIBDIR = $$prefix/lib
    QMAKE_PKGCONFIG_INCDIR = $$prefix/include
    QMAKE_PKGCONFIG_DESTDIR = pkgconfig
    INSTALLS    += headers target
}
