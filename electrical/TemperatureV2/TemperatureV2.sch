EESchema Schematic File Version 4
EELAYER 30 0
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
L Feather:FeatherM0 U1
U 1 1 60834D65
P 4400 2450
F 0 "U1" H 4400 3465 50  0000 C CNN
F 1 "FeatherM0" H 4400 3374 50  0000 C CNN
F 2 "Feather:FeatherM0" H 4400 2500 50  0001 C CNN
F 3 "" H 4400 2500 50  0001 C CNN
	1    4400 2450
	1    0    0    -1  
$EndComp
$Comp
L Feather:PoeFeatherWing U4
U 1 1 608386C1
P 6950 2450
F 0 "U4" H 6925 3465 50  0000 C CNN
F 1 "PoeFeatherWing" H 6925 3374 50  0000 C CNN
F 2 "Feather:EthernetWing" H 6950 2500 50  0001 C CNN
F 3 "" H 6950 2500 50  0001 C CNN
	1    6950 2450
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Temperature:DS18B20 U2
U 1 1 60839A9C
P 6850 4250
F 0 "U2" H 6620 4296 50  0000 R CNN
F 1 "DS18B20" H 6620 4205 50  0000 R CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 5850 4000 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS18B20.pdf" H 6700 4500 50  0001 C CNN
	1    6850 4250
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Temperature:DS18B20 U3
U 1 1 6083AC61
P 6850 5250
F 0 "U3" H 6620 5296 50  0000 R CNN
F 1 "DS18B20" H 6620 5205 50  0000 R CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 5850 5000 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS18B20.pdf" H 6700 5500 50  0001 C CNN
	1    6850 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 6083B8FB
P 4550 4600
F 0 "R1" H 4620 4646 50  0000 L CNN
F 1 "4.7k" H 4620 4555 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4480 4600 50  0001 C CNN
F 3 "~" H 4550 4600 50  0001 C CNN
	1    4550 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 1900 5150 1900
Wire Wire Line
	5150 1900 5150 1800
Wire Wire Line
	4850 2000 5300 2000
Wire Wire Line
	4850 1700 5300 1700
Text Label 5300 1700 0    50   ~ 0
3v3
Text Label 5300 1800 0    50   ~ 0
GND
Text Label 5300 2000 0    50   ~ 0
VUSB
Text Label 7650 2000 0    50   ~ 0
VUSB
Wire Wire Line
	7400 2000 7650 2000
Wire Wire Line
	7400 1800 7550 1800
Wire Wire Line
	7400 1900 7550 1900
Wire Wire Line
	7550 1900 7550 1800
Connection ~ 7550 1800
Text Label 7650 1800 0    50   ~ 0
GND
Wire Wire Line
	7400 1700 7650 1700
Text Label 7650 1700 0    50   ~ 0
3v3
Wire Wire Line
	7400 2750 7650 2750
Wire Wire Line
	7400 2850 7650 2850
Wire Wire Line
	7400 2950 7650 2950
Wire Wire Line
	7400 3100 7650 3100
Wire Wire Line
	7400 3200 7650 3200
Text Label 7650 2750 0    50   ~ 0
SCK
Text Label 7650 2850 0    50   ~ 0
MOSI
Text Label 7650 2950 0    50   ~ 0
MISO
Text Label 7650 3100 0    50   ~ 0
SDA
Text Label 7650 3200 0    50   ~ 0
SCL
Wire Wire Line
	6500 2900 6150 2900
Text Label 6150 2900 0    50   ~ 0
CS
Text Label 3550 2900 0    50   ~ 0
CS
Wire Wire Line
	3550 2900 3950 2900
Wire Wire Line
	4850 2750 5300 2750
Wire Wire Line
	4850 2850 5300 2850
Wire Wire Line
	4850 2950 5300 2950
Wire Wire Line
	4850 3100 5300 3100
Wire Wire Line
	4850 3200 5300 3200
Text Label 5300 3200 0    50   ~ 0
SCL
Text Label 5300 3100 0    50   ~ 0
SDA
Text Label 5300 2950 0    50   ~ 0
MISO
Text Label 5300 2850 0    50   ~ 0
MOSI
Text Label 5300 2750 0    50   ~ 0
SCK
Text Label 4550 4300 0    50   ~ 0
3v3
Wire Wire Line
	4550 4300 4550 4450
Text Label 4550 4950 0    50   ~ 0
SENSOR
Wire Wire Line
	4550 4750 4550 4950
Wire Wire Line
	3550 2700 3950 2700
Text Label 3550 2700 0    50   ~ 0
SENSOR
Text Label 7400 4250 0    50   ~ 0
SENSOR
Text Label 7400 5250 0    50   ~ 0
SENSOR
Wire Wire Line
	7400 5250 7150 5250
Wire Wire Line
	7150 4250 7400 4250
Text Label 6850 4700 0    50   ~ 0
GND
Text Label 6850 5750 0    50   ~ 0
GND
Wire Wire Line
	6850 5550 6850 5750
Wire Wire Line
	6850 4700 6850 4550
Text Label 6850 4850 0    50   ~ 0
3v3
Text Label 6850 3800 0    50   ~ 0
3v3
Wire Wire Line
	6850 3800 6850 3950
Wire Wire Line
	6850 4850 6850 4950
NoConn ~ 3950 1700
NoConn ~ 3950 1800
NoConn ~ 3950 1950
NoConn ~ 3950 2050
NoConn ~ 3950 2150
NoConn ~ 3950 2250
NoConn ~ 3950 2350
NoConn ~ 3950 2450
NoConn ~ 3950 2600
NoConn ~ 3950 2800
NoConn ~ 3950 3000
NoConn ~ 3950 3100
NoConn ~ 3950 3200
NoConn ~ 4850 2600
NoConn ~ 4850 2500
NoConn ~ 4850 2200
NoConn ~ 4850 2100
$Comp
L power:GND #PWR0101
U 1 1 6085E995
P 5750 1850
F 0 "#PWR0101" H 5750 1600 50  0001 C CNN
F 1 "GND" H 5755 1677 50  0000 C CNN
F 2 "" H 5750 1850 50  0001 C CNN
F 3 "" H 5750 1850 50  0001 C CNN
	1    5750 1850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 6085F91B
P 8050 1850
F 0 "#PWR0102" H 8050 1600 50  0001 C CNN
F 1 "GND" H 8055 1677 50  0000 C CNN
F 2 "" H 8050 1850 50  0001 C CNN
F 3 "" H 8050 1850 50  0001 C CNN
	1    8050 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 1800 8050 1800
Wire Wire Line
	4850 1800 5150 1800
Connection ~ 5150 1800
NoConn ~ 6500 1700
NoConn ~ 6500 1800
NoConn ~ 6500 1950
NoConn ~ 6500 2050
NoConn ~ 6500 2150
NoConn ~ 6500 2250
NoConn ~ 6500 2350
NoConn ~ 6500 2450
NoConn ~ 6500 2600
NoConn ~ 6500 2700
NoConn ~ 6500 2800
NoConn ~ 6500 3000
NoConn ~ 6500 3100
NoConn ~ 6500 3200
NoConn ~ 7400 2600
NoConn ~ 7400 2500
NoConn ~ 7400 2200
NoConn ~ 7400 2100
Wire Wire Line
	5150 1800 5750 1800
Wire Wire Line
	5750 1850 5750 1800
Wire Wire Line
	8050 1850 8050 1800
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 6086C480
P 5750 1800
F 0 "#FLG0101" H 5750 1875 50  0001 C CNN
F 1 "PWR_FLAG" H 5750 1973 50  0001 C CNN
F 2 "" H 5750 1800 50  0001 C CNN
F 3 "~" H 5750 1800 50  0001 C CNN
	1    5750 1800
	1    0    0    -1  
$EndComp
Connection ~ 5750 1800
$EndSCHEMATC
