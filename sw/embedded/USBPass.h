/*
			USBPass
  Copyright (C) Josh Watts, 2013

     josh [at] sroz [dot] net
	      www.sroz.net


  Original code copyright and license:
*/
/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2010  Matthias Hullin (lufa [at] matthias [dot] hullin [dot] net)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Header file for USBPass.c.
 */

#ifndef _USBPASS_H_
#define _USBPASS_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>
		#include <avr/interrupt.h>
		#include <avr/interrupt.h>
		#include <avr/wdt.h>
		#include <stdbool.h>
		#include <string.h>

		#include "Descriptors.h"

		#include "Config/AppConfig.h"

		#include "Lib/action.h"
		#include "Lib/button.h"
		#include "Lib/settings.h"
		#include "Lib/timer.h"
		#include "Lib/debug.h"
		#include "Lib/hid_keyboard.h"
		#include "Lib/scancodes.h"
		#include "Lib/key_store.h"

		#include "pin_map.h"

		#include <LUFA/Drivers/Board/LEDs.h>
		#include <LUFA/Drivers/Peripheral/Serial.h>
		#include <LUFA/Drivers/USB/USB.h>

	/* Macros: */
		/** LED mask for the library LED driver, to indicate that the USB interface is not ready. */
		#define LEDMASK_USB_NOTREADY      LEDS_LED1

		/** LED mask for the library LED driver, to indicate that the USB interface is enumerating. */
		#define LEDMASK_USB_ENUMERATING  (LEDS_LED2 | LEDS_LED3)

		/** LED mask for the library LED driver, to indicate that the USB interface is ready. */
		#define LEDMASK_USB_READY        (LEDS_LED2 | LEDS_LED4)

		/** LED mask for the library LED driver, to indicate that an error has occurred in the USB interface. */
		#define LEDMASK_USB_ERROR        (LEDS_LED1 | LEDS_LED3)

		/** LED mask for the library LED driver, to indicate that the USB interface is busy. */
		#define LEDMASK_USB_BUSY         LEDS_LED2

		#define REPORT_ID_SET_KEY 1
		#define REPORT_ID_SET_NAME 2
		#define REPORT_ID_SET_COMMIT_KEY 3
		#define REPORT_ID_SET_NUM_KEYS 4
		#define REPORT_ID_SET_QUICK_KEY 5
		#define REPORT_ID_SET_ACTION 6
		#define REPORT_ID_RESET 0xFF

	/* Function Prototypes: */
		void SetupHardware(void);
		void SetupButtons(void);
		void CheckButtons(void);
		void TeardownHardware(void);
		void SaveButtonAction(int button_id, int action_id);

		void EVENT_USB_Device_Connect(void);
		void EVENT_USB_Device_Disconnect(void);
		void EVENT_USB_Device_ConfigurationChanged(void);
		void EVENT_USB_Device_ControlRequest(void);
		void EVENT_USB_Device_StartOfFrame(void);

		bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
		                                         uint8_t* const ReportID,
		                                         const uint8_t ReportType,
		                                         void* ReportData,
		                                         uint16_t* const ReportSize);
		void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
		                                          const uint8_t ReportID,
		                                          const uint8_t ReportType,
		                                          const void* ReportData,
		                                          const uint16_t ReportSize);

#endif

