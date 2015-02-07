EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:atmega32u2
LIBS:goodfet31_kicad-cache
LIBS:sw_push2
LIBS:MKL25ZxVFM4
LIBS:usbpass-cache
EELAYER 24 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "27 jan 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 7800 4550 2    60   ~ 0
MCU_nRESET
$Comp
L R R?
U 1 1 510413E4
P 10200 3900
F 0 "R?" V 10280 3900 50  0000 C CNN
F 1 "10K" V 10200 3900 50  0000 C CNN
F 2 "" H 10200 3900 60  0001 C CNN
F 3 "" H 10200 3900 60  0001 C CNN
	1    10200 3900
	-1   0    0    1   
$EndComp
Text Label 1300 1250 0    60   ~ 0
GND
Text Label 1650 950  2    60   ~ 0
USB_5V
Text Label 2750 1150 2    60   ~ 0
MCU_USB_P
Text Label 2750 1050 2    60   ~ 0
MCU_USB_M
Text Label 1300 1150 0    60   ~ 0
USB_P
Text Label 1300 1050 0    60   ~ 0
USB_M
$Comp
L R R?
U 1 1 5101E0DC
P 1900 1150
F 0 "R?" V 1950 950 50  0000 C CNN
F 1 "22 5%" V 1900 1150 50  0000 C CNN
F 2 "" H 1900 1150 60  0001 C CNN
F 3 "" H 1900 1150 60  0001 C CNN
	1    1900 1150
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 5101E0D6
P 1900 1050
F 0 "R?" V 1950 850 50  0000 C CNN
F 1 "22 5%" V 1900 1050 50  0000 C CNN
F 2 "" H 1900 1050 60  0001 C CNN
F 3 "" H 1900 1050 60  0001 C CNN
	1    1900 1050
	0    1    1    0   
$EndComp
$Comp
L GND #PWR010
U 1 1 5101D99B
P 1650 1400
F 0 "#PWR010" H 1650 1400 30  0001 C CNN
F 1 "GND" H 1650 1330 30  0001 C CNN
F 2 "" H 1650 1400 60  0001 C CNN
F 3 "" H 1650 1400 60  0001 C CNN
	1    1650 1400
	1    0    0    -1  
$EndComp
$Comp
L USB_2 J1
U 1 1 5101D8AA
P 1050 1100
F 0 "J1" H 975 1350 60  0000 C CNN
F 1 "USB_2" H 1100 800 60  0001 C CNN
F 2 "" H 1050 1100 60  0001 C CNN
F 3 "" H 1050 1100 60  0001 C CNN
F 4 "VCC" H 1375 1250 50  0001 C CNN "VCC"
F 5 "D+" H 1350 1150 50  0001 C CNN "Data+"
F 6 "D-" H 1350 1050 50  0001 C CNN "Data-"
F 7 "GND" H 1375 950 50  0001 C CNN "Ground"
	1    1050 1100
	1    0    0    -1  
$EndComp
$Comp
L MKL25ZXVFM4 U?
U 1 1 52F012E0
P 5600 4000
F 0 "U?" H 5600 3900 50  0000 C CNN
F 1 "MKL25ZXVFM4" H 5600 4100 50  0000 C CNN
F 2 "MODULE" H 5600 4000 50  0001 C CNN
F 3 "DOCUMENTATION" H 5600 4000 50  0001 C CNN
	1    5600 4000
	1    0    0    -1  
$EndComp
Text Label 3500 3750 0    60   ~ 0
MCU_VREGIN
$Comp
L GS3 GS?
U 1 1 52F013E7
P 3850 1150
F 0 "GS?" H 3900 1350 50  0000 C CNN
F 1 "GS3" H 3900 951 40  0000 C CNN
F 2 "" H 3850 1150 60  0000 C CNN
F 3 "" H 3850 1150 60  0000 C CNN
	1    3850 1150
	1    0    0    -1  
$EndComp
Text Label 3200 1050 0    60   ~ 0
USB_5V
Text Label 3200 1250 0    60   ~ 0
EXT_5V
Text Label 4650 1150 2    60   ~ 0
MCU_VREGIN
Text Label 3500 3450 0    60   ~ 0
MCU_USB_P
Text Label 3500 3550 0    60   ~ 0
MCU_USB_M
Text Label 3500 3650 0    60   ~ 0
MCU_VOUT33
Text Label 3500 4650 0    60   ~ 0
MCU_VDD
$Comp
L GS3 GS?
U 1 1 52F7A1AA
P 3850 1650
F 0 "GS?" H 3900 1850 50  0000 C CNN
F 1 "GS3" H 3900 1451 40  0000 C CNN
F 2 "" H 3850 1650 60  0000 C CNN
F 3 "" H 3850 1650 60  0000 C CNN
	1    3850 1650
	1    0    0    -1  
$EndComp
Text Label 4500 1650 2    60   ~ 0
MCU_VDD
Text Label 3100 1550 0    60   ~ 0
MCU_VOUT33
Text Label 3500 3850 0    60   ~ 0
MCU_VDDA
Text Label 9750 3600 0    60   ~ 0
MCU_VDD
Text Label 3100 1750 0    60   ~ 0
EXT_3V3
$Comp
L GND #PWR?
U 1 1 52F7B5AA
P 1200 1950
F 0 "#PWR?" H 1200 1950 30  0001 C CNN
F 1 "GND" H 1200 1880 30  0001 C CNN
F 2 "" H 1200 1950 60  0001 C CNN
F 3 "" H 1200 1950 60  0001 C CNN
	1    1200 1950
	1    0    0    -1  
$EndComp
Text Label 900  1550 0    60   ~ 0
USB_5V
Text Label 9500 4250 0    60   ~ 0
MCU_nRESET
$Comp
L CSMALL C?
U 1 1 52F7B68E
P 1200 1750
F 0 "C?" H 1225 1800 30  0000 L CNN
F 1 "CSMALL" H 1225 1700 30  0000 L CNN
F 2 "" H 1200 1750 60  0000 C CNN
F 3 "" H 1200 1750 60  0000 C CNN
	1    1200 1750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 52F7B69E
P 10100 4650
F 0 "#PWR?" H 10100 4650 30  0001 C CNN
F 1 "GND" H 10100 4580 30  0001 C CNN
F 2 "" H 10100 4650 60  0001 C CNN
F 3 "" H 10100 4650 60  0001 C CNN
	1    10100 4650
	1    0    0    -1  
$EndComp
$Comp
L CSMALL C?
U 1 1 52F7B6A4
P 10100 4450
F 0 "C?" H 10125 4500 30  0000 L CNN
F 1 "CSMALL" H 10125 4400 30  0000 L CNN
F 2 "" H 10100 4450 60  0000 C CNN
F 3 "" H 10100 4450 60  0000 C CNN
	1    10100 4450
	1    0    0    -1  
$EndComp
Text Label 3500 3950 0    60   ~ 0
MCU_VSSA
$Comp
L GND #PWR?
U 1 1 52F7B747
P 3300 3450
F 0 "#PWR?" H 3300 3450 30  0001 C CNN
F 1 "GND" H 3300 3380 30  0001 C CNN
F 2 "" H 3300 3450 60  0001 C CNN
F 3 "" H 3300 3450 60  0001 C CNN
	1    3300 3450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 52F7B74D
P 3300 4850
F 0 "#PWR?" H 3300 4850 30  0001 C CNN
F 1 "GND" H 3300 4780 30  0001 C CNN
F 2 "" H 3300 4850 60  0001 C CNN
F 3 "" H 3300 4850 60  0001 C CNN
	1    3300 4850
	1    0    0    -1  
$EndComp
Text Label 7800 3950 2    60   ~ 0
MCU_UART1_TX
Text Label 7800 4050 2    60   ~ 0
MCU_UART1_RX
$Comp
L GND #PWR?
U 1 1 52F7BD6F
P 5450 1550
F 0 "#PWR?" H 5450 1550 30  0001 C CNN
F 1 "GND" H 5450 1480 30  0001 C CNN
F 2 "" H 5450 1550 60  0001 C CNN
F 3 "" H 5450 1550 60  0001 C CNN
	1    5450 1550
	1    0    0    -1  
$EndComp
Text Label 5750 900  0    60   ~ 0
MCU_VDD
Text Label 5750 1000 0    60   ~ 0
MCU_SWD_DIO
Text Label 5750 1200 0    60   ~ 0
MCU_SWD_CLK
Text Label 5750 1800 0    60   ~ 0
MCU_nRESET
Text Label 3500 4450 0    60   ~ 0
MCU_SWD_DIO
Text Label 3500 4150 0    60   ~ 0
MCU_SWD_CLK
Text Notes 700  700  0    60   ~ 0
USB
Text Notes 3000 700  0    60   ~ 0
Power selection
Text Notes 5000 700  0    60   ~ 0
SWD Connector
$Comp
L CONN_1 TP?
U 1 1 52F7C0FB
P 7850 1000
F 0 "TP?" H 7930 1000 40  0000 L CNN
F 1 "CONN_1" H 7850 1055 30  0001 C CNN
F 2 "" H 7850 1000 60  0000 C CNN
F 3 "" H 7850 1000 60  0000 C CNN
	1    7850 1000
	0    -1   -1   0   
$EndComp
Text Label 7850 1800 1    60   ~ 0
MCU_nRESET
$Comp
L CONN_1 TP?
U 1 1 52F7C195
P 8100 1000
F 0 "TP?" H 8180 1000 40  0000 L CNN
F 1 "CONN_1" H 8100 1055 30  0001 C CNN
F 2 "" H 8100 1000 60  0000 C CNN
F 3 "" H 8100 1000 60  0000 C CNN
	1    8100 1000
	0    -1   -1   0   
$EndComp
Text Label 8100 1800 1    60   ~ 0
MCU_VDD
$Comp
L CONN_1 TP?
U 1 1 52F7C1A1
P 8350 1000
F 0 "TP?" H 8430 1000 40  0000 L CNN
F 1 "CONN_1" H 8350 1055 30  0001 C CNN
F 2 "" H 8350 1000 60  0000 C CNN
F 3 "" H 8350 1000 60  0000 C CNN
	1    8350 1000
	0    -1   -1   0   
$EndComp
Text Label 8350 1800 1    60   ~ 0
GND
Text Label 3500 4250 0    60   ~ 0
MCU_TSI_CH2
Text Label 3500 4350 0    60   ~ 0
MCU_TSI_CH3
Text Label 3500 4550 0    60   ~ 0
MCU_TSI_CH5
Text Label 7800 4350 2    60   ~ 0
MCU_TSI_CH6
Text Label 7800 4450 2    60   ~ 0
MCU_TSI_CH0
Text Label 7800 3850 2    60   ~ 0
MCU_SPI_CLK
Text Label 7800 3750 2    60   ~ 0
MCU_SPI_MOSI
Text Label 7800 3650 2    60   ~ 0
MCU_SPI_MISO
Wire Wire Line
	4150 3550 3500 3550
Wire Wire Line
	4150 3450 3500 3450
Wire Wire Line
	4000 1150 4650 1150
Wire Wire Line
	3700 1250 3200 1250
Wire Wire Line
	3700 1050 3200 1050
Wire Wire Line
	4150 3750 3500 3750
Wire Wire Line
	1250 1150 1650 1150
Wire Wire Line
	2150 1050 2750 1050
Wire Wire Line
	1250 1250 1650 1250
Wire Wire Line
	1650 1250 1650 1400
Wire Wire Line
	1250 950  1650 950 
Wire Wire Line
	2150 1150 2750 1150
Wire Wire Line
	1250 1050 1650 1050
Wire Wire Line
	7800 4550 7050 4550
Wire Wire Line
	4150 3650 3500 3650
Wire Wire Line
	4150 4650 3500 4650
Wire Wire Line
	4000 1650 4500 1650
Wire Wire Line
	3700 1550 3100 1550
Wire Wire Line
	3700 1750 3100 1750
Wire Wire Line
	3500 3850 4150 3850
Wire Wire Line
	1200 1650 1200 1550
Wire Wire Line
	1200 1550 900  1550
Wire Wire Line
	1200 1850 1200 1950
Wire Wire Line
	10200 4250 10200 4150
Wire Wire Line
	9500 4250 10100 4250
Wire Wire Line
	10100 4250 10200 4250
Wire Wire Line
	7850 1150 7850 1800
Wire Wire Line
	10200 3650 10200 3600
Wire Wire Line
	10200 3600 9750 3600
Wire Wire Line
	10100 4550 10100 4650
Wire Wire Line
	10100 4350 10100 4250
Wire Wire Line
	4150 3950 3500 3950
Wire Wire Line
	4150 3350 3300 3350
Wire Wire Line
	3300 3350 3300 3450
Wire Wire Line
	4150 4750 3300 4750
Wire Wire Line
	3300 4750 3300 4850
Wire Wire Line
	7050 4050 7800 4050
Wire Wire Line
	7050 3950 7800 3950
Wire Wire Line
	6500 1000 5750 1000
Wire Wire Line
	6500 1200 5750 1200
Wire Wire Line
	6500 1800 5750 1800
Wire Wire Line
	6500 1100 5450 1100
Wire Wire Line
	5450 1100 5450 1300
Wire Wire Line
	5450 1300 5450 1550
Wire Wire Line
	6500 1300 5450 1300
Connection ~ 5450 1300
Wire Wire Line
	5750 900  6500 900 
Wire Wire Line
	4150 4450 3500 4450
Wire Wire Line
	4150 4150 3500 4150
Wire Notes Line
	700  700  2850 700 
Wire Notes Line
	2850 700  2850 2100
Wire Notes Line
	2850 2100 700  2100
Wire Notes Line
	700  2100 700  700 
Wire Notes Line
	3000 700  4800 700 
Wire Notes Line
	4800 700  4800 2100
Wire Notes Line
	4800 2100 3000 2100
Wire Notes Line
	3000 2100 3000 700 
Wire Notes Line
	5000 700  7350 700 
Wire Notes Line
	7350 700  7350 2100
Wire Notes Line
	7350 2100 5000 2100
Wire Notes Line
	5000 2100 5000 700 
Connection ~ 10200 4250
Connection ~ 10100 4250
Wire Wire Line
	8100 1150 8100 1800
Wire Wire Line
	8350 1150 8350 1800
Wire Wire Line
	4150 4250 3500 4250
Wire Wire Line
	4150 4350 3500 4350
Wire Wire Line
	4150 4550 3500 4550
Wire Wire Line
	7050 4450 7800 4450
Wire Wire Line
	7050 4350 7800 4350
Wire Wire Line
	7050 3850 7800 3850
Wire Wire Line
	7050 3750 7800 3750
Wire Wire Line
	7050 3650 7800 3650
Wire Wire Line
	7050 3550 7800 3550
Wire Wire Line
	7050 3450 7800 3450
Text Label 7800 3450 2    60   ~ 0
MCU_UART2_RX
Text Label 7800 3550 2    60   ~ 0
MCU_UART2_TX
Wire Notes Line
	7550 700  8650 700 
Wire Notes Line
	8650 700  8650 2100
Wire Notes Line
	8650 2100 7550 2100
Wire Notes Line
	7550 2100 7550 700 
Text Notes 7550 700  0    60   ~ 0
Test points
$Comp
L CONN_10 P?
U 1 1 52F82F83
P 6850 1350
F 0 "P?" V 6800 1350 60  0000 C CNN
F 1 "CONN_10" V 6900 1350 60  0000 C CNN
F 2 "" H 6850 1350 60  0000 C CNN
F 3 "" H 6850 1350 60  0000 C CNN
	1    6850 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 1400 5750 1400
Wire Wire Line
	6500 1500 5750 1500
Wire Wire Line
	6500 1600 5750 1600
Wire Wire Line
	6500 1700 5750 1700
Text Label 5750 1400 0    60   ~ 0
MCU_UART2_RX
Text Label 5750 1500 0    60   ~ 0
MCU_UART2_TX
$EndSCHEMATC
