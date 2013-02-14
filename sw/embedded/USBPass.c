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
 *  Main source file for the USBPass device firmware. This file contains the main tasks of
 *  the firmware and is responsible for the initial application hardware configuration.
 */

#define ENABLE_USB
#include "USBPass.h"

/** Button state objects */
static button_obj_t buttons[NUM_BUTTONS];

/** Buffer to hold the previously generated Keyboard HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevKeyboardHIDReportBuffer[sizeof(USB_KeyboardReport_Data_t)];

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_Device_t Keyboard_HID_Interface =
 	{
		.Config =
			{
				.InterfaceNumber              = 1,
				.ReportINEndpoint             =
					{
						.Address              = KEYBOARD_EPADDR,
						.Size                 = KEYBOARD_EPSIZE,
						.Banks                = 1,
					},
				.PrevReportINBuffer           = PrevKeyboardHIDReportBuffer,
				.PrevReportINBufferSize       = sizeof(PrevKeyboardHIDReportBuffer),
			},
    };

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	sei();

	DBG("Enter main loop\r\n");
	
	for (;;)
	{
		CheckButtons();
#ifdef ENABLE_USB
		HID_Device_USBTask(&Keyboard_HID_Interface);
		USB_USBTask();
#endif
	}
}

/** Configures the board hardware and chip peripherals for the firmware's functionality. */
void SetupHardware(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	/* Hardware Initialization */
	LEDs_Init();
	Serial_Init(9600, false);
	Serial_CreateStream(NULL);
	settings_init();
#ifdef ENABLE_USB
	USB_Init();
#endif
	timer_init();
	SetupButtons();

}

/** Configure buttons from stored settings */
void SetupButtons(void)
{
	button_obj_t *b = NULL;

	MCUCR &= ~(1<<PUD);
	DDRD &= ~((1<<SW1_PIN)|(1<<SW2_PIN|(1<<SW3_PIN)));
	PORTD |= (1<<SW1_PIN)|(1<<SW2_PIN|(1<<SW3_PIN));

	b = &buttons[BUTTON_SW1];
	button_init(b);
	b->port = &SW1_PORT;
	b->pin = SW1_PIN;
	map_button_to_action(b, ACTION_TYPE_SHORT, settings_get_int(SETTINGS_SW1_ACTION));
	map_button_to_action(b, ACTION_TYPE_LONG, settings_get_int(SETTINGS_SW1_LONG_ACTION));

	b = &buttons[BUTTON_SW2];
	button_init(b);
	b->port = &SW2_PORT;
	b->pin = SW2_PIN;
	map_button_to_action(b, ACTION_TYPE_SHORT, settings_get_int(SETTINGS_SW2_ACTION));
	map_button_to_action(b, ACTION_TYPE_LONG, settings_get_int(SETTINGS_SW2_LONG_ACTION));

	b = &buttons[BUTTON_SW3];
	button_init(b);
	b->port = &SW3_PORT;
	b->pin = SW3_PIN;
	map_button_to_action(b, ACTION_TYPE_SHORT, settings_get_int(SETTINGS_SW3_ACTION));
	map_button_to_action(b, ACTION_TYPE_LONG, settings_get_int(SETTINGS_SW3_LONG_ACTION));
}

/** Check each button to see if an action has occurred */
void CheckButtons(void)
{
	button_check(&buttons[BUTTON_SW1]);
	button_check(&buttons[BUTTON_SW2]);
	button_check(&buttons[BUTTON_SW3]);
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	ConfigSuccess &= HID_Device_ConfigureEndpoints(&Keyboard_HID_Interface);

	USB_Device_EnableSOFEvents();

	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	HID_Device_ProcessControlRequest(&Keyboard_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void)
{
    HID_Device_MillisecondElapsed(&Keyboard_HID_Interface);
}

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
 *
 *  \return Boolean true to force the sending of the report, false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{
	static bool key_pressed = false;
	bool retval = false;
	USB_KeyboardReport_Data_t* KeyboardReport = (USB_KeyboardReport_Data_t*)ReportData;

	//TODO: Implement delay if desired (I think this will chew through keys at the speed of HID reports?

	if (!key_pressed) {
		char key = hid_key_get_key();
		if (key != '\0') {
			retval = ascii_to_scancode(key, &KeyboardReport->KeyCode[0], &KeyboardReport->Modifier);
		}
	} else {
		KeyboardReport->Modifier = 0;
		KeyboardReport->KeyCode[0] = 0;
	}
	key_pressed = retval;

	*ReportSize = sizeof(USB_KeyboardReport_Data_t);

	return retval;
}

/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
	//TODO: Potentially react to NUMLOCK/CAPSLOCK/SCROLLLOCK sequences
#if 0
	uint8_t  LEDMask   = LEDS_NO_LEDS;
	uint8_t* LEDReport = (uint8_t*)ReportData;

	if (*LEDReport & HID_KEYBOARD_LED_NUMLOCK)
	  LEDMask |= LEDS_LED1;

	if (*LEDReport & HID_KEYBOARD_LED_CAPSLOCK)
	  LEDMask |= LEDS_LED3;

	if (*LEDReport & HID_KEYBOARD_LED_SCROLLLOCK)
	  LEDMask |= LEDS_LED4;

	LEDs_SetAllLEDs(LEDMask);
#endif
}

