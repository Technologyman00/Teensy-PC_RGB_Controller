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
L Connector:Conn_01x24_Female J1
U 1 1 5FE90075
P 4600 3700
F 0 "J1" H 4628 3676 50  0000 L CNN
F 1 "Conn_01x24_Female" H 4628 3585 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x24_P2.54mm_Horizontal" H 4600 3700 50  0001 C CNN
F 3 "~" H 4600 3700 50  0001 C CNN
	1    4600 3700
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x24_Female J2
U 1 1 5FE94ABA
P 6050 3750
F 0 "J2" H 6078 3726 50  0000 L CNN
F 1 "Conn_01x24_Female" H 6078 3635 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x24_P2.54mm_Vertical" H 6050 3750 50  0001 C CNN
F 3 "~" H 6050 3750 50  0001 C CNN
	1    6050 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 5FE974BE
P 3150 2800
F 0 "D1" H 3143 3017 50  0000 C CNN
F 1 "LED" H 3143 2926 50  0000 C CNN
F 2 "LED_THT:LED_D1.8mm_W1.8mm_H2.4mm_Horizontal_O1.27mm_Z1.6mm" H 3150 2800 50  0001 C CNN
F 3 "~" H 3150 2800 50  0001 C CNN
	1    3150 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5FE97DCC
P 3550 2200
F 0 "R1" H 3620 2246 50  0000 L CNN
F 1 "R" H 3620 2155 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P15.24mm_Horizontal" V 3480 2200 50  0001 C CNN
F 3 "~" H 3550 2200 50  0001 C CNN
	1    3550 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 2800 3000 2050
Wire Wire Line
	3000 2050 3550 2050
Wire Wire Line
	3550 2350 3550 2600
Wire Wire Line
	3550 2600 4400 2600
Wire Wire Line
	3300 2800 4400 2800
Wire Wire Line
	4400 2800 4400 2700
Connection ~ 4400 2800
$EndSCHEMATC
