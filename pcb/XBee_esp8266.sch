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
LIBS:XBee_esp8266-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_01X10 P4
U 1 1 54AFDADA
P 6800 3750
F 0 "P4" H 6800 4300 50  0000 C CNN
F 1 "CONN_XBEE2" V 6900 3750 50  0000 C CNN
F 2 "XBEE:1x10_2MM" H 6800 3750 60  0001 C CNN
F 3 "" H 6800 3750 60  0000 C CNN
	1    6800 3750
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X10 P1
U 1 1 54AFDB5E
P 4950 3750
F 0 "P1" H 4950 4300 50  0000 C CNN
F 1 "CONN_XBEE1" V 5050 3750 50  0000 C CNN
F 2 "XBEE:1x10_2MM" H 4950 3750 60  0001 C CNN
F 3 "" H 4950 3750 60  0000 C CNN
	1    4950 3750
	-1   0    0    -1  
$EndComp
$Comp
L CONN_02X04 P3
U 1 1 54AFDD01
P 5850 3950
F 0 "P3" H 5850 4200 50  0000 C CNN
F 1 "CONN_ESP8266" H 5850 3700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x04" H 5850 2750 60  0001 C CNN
F 3 "" H 5850 2750 60  0000 C CNN
	1    5850 3950
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 54AFDD43
P 5850 4500
F 0 "SW1" H 6000 4610 50  0000 C CNN
F 1 "SW_CONFIG" H 5850 4420 50  0000 C CNN
F 2 "Discret:SW_PUSH_SMALL" H 5850 4500 60  0001 C CNN
F 3 "" H 5850 4500 60  0000 C CNN
	1    5850 4500
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR01
U 1 1 54AFDD7A
P 5150 3150
F 0 "#PWR01" H 5150 3110 30  0001 C CNN
F 1 "+3.3V" H 5150 3260 30  0000 C CNN
F 2 "" H 5150 3150 60  0000 C CNN
F 3 "" H 5150 3150 60  0000 C CNN
	1    5150 3150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 54AFDDAC
P 5150 4350
F 0 "#PWR02" H 5150 4350 30  0001 C CNN
F 1 "GND" H 5150 4280 30  0001 C CNN
F 2 "" H 5150 4350 60  0000 C CNN
F 3 "" H 5150 4350 60  0000 C CNN
	1    5150 4350
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X06 P2
U 1 1 54AFDE68
P 5850 2900
F 0 "P2" H 5850 3250 50  0000 C CNN
F 1 "CONN_SERIAL" V 5950 2900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06" H 5850 2900 60  0001 C CNN
F 3 "" H 5850 2900 60  0000 C CNN
	1    5850 2900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5150 3150 5150 3300
Wire Wire Line
	5150 4200 5150 4350
Wire Wire Line
	5400 4200 5150 4200
Wire Wire Line
	5400 3200 5400 4200
Wire Wire Line
	5400 3800 5600 3800
Wire Wire Line
	6100 4100 6200 4100
Wire Wire Line
	6200 4100 6200 3300
Wire Wire Line
	6200 3300 5150 3300
Wire Wire Line
	5150 3500 5700 3500
Wire Wire Line
	5500 3500 5500 4100
Wire Wire Line
	5500 4100 5600 4100
Wire Wire Line
	5400 3200 6100 3200
Wire Wire Line
	6100 3200 6100 3100
Connection ~ 5400 3800
Wire Wire Line
	6100 3800 6100 3400
Wire Wire Line
	6100 3400 5600 3400
Wire Wire Line
	5600 3400 5600 3100
Wire Wire Line
	5700 3500 5700 3100
Connection ~ 5500 3500
Wire Wire Line
	5600 4000 5450 4000
Wire Wire Line
	5450 4000 5450 4500
Wire Wire Line
	5450 4500 5550 4500
Wire Wire Line
	6150 4500 6150 4650
Wire Wire Line
	6150 4650 5300 4650
Wire Wire Line
	5300 4650 5300 4200
Connection ~ 5300 4200
Wire Wire Line
	6100 3900 6200 3900
Connection ~ 6200 3900
$EndSCHEMATC