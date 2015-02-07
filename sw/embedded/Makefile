#
#			USBPass
#  Copyright (C) Josh Watts, 2013
#
#     josh [at] sroz [dot] net
#	      www.sroz.net
#
#
#  Original code copyright and license:
#
#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

MCU          = atmega32u2
ARCH         = AVR8
BOARD        = BOARD_USER
F_CPU        = 8000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = USBPass
SRC          = $(TARGET).c Descriptors.c $(wildcard Lib/*.c) $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS)
SRC          += $(LUFA_SRC_SERIAL)
ifeq ($(LUFA_PATH),)
$(error "You must export LUFA_PATH before calling this Makefile")
endif
LUFA_PATH    := ${LUFA_PATH}/LUFA
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IConfig/
LD_FLAGS     =

ifneq ($(DEBUG),)
CC_FLAGS     += -DDEBUG
endif

# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk
