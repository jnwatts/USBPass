#!/bin/sh

sudo LD_LIBRARY_PATH=../hidapi/libusb/.libs/ ./usbpass setnumkeys 1
sudo LD_LIBRARY_PATH=../hidapi/libusb/.libs/ ./usbpass setkey 0 asdf 1234
sudo LD_LIBRARY_PATH=../hidapi/libusb/.libs/ ./usbpass setquickkey 0 0
sudo LD_LIBRARY_PATH=../hidapi/libusb/.libs/ ./usbpass reset
