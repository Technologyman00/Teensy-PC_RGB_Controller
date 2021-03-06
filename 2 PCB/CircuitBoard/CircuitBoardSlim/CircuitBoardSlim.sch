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
L TXS0108EPWR:TXS0108EPWR U1
U 1 1 60AE0167
P 4300 1650
F 0 "U1" H 4300 2720 50  0000 C CNN
F 1 "TXS0108EPWR" H 4300 2629 50  0000 C CNN
F 2 "SOP65P640X120-20N" H 4300 1650 50  0001 L BNN
F 3 "" H 4300 1650 50  0001 L BNN
	1    4300 1650
	1    0    0    -1  
$EndComp
$Comp
L TXS0108EPWR:TXS0108EPWR U2
U 1 1 60AE1EF2
P 4300 3700
F 0 "U2" H 4300 4770 50  0000 C CNN
F 1 "TXS0108EPWR" H 4300 4679 50  0000 C CNN
F 2 "SOP65P640X120-20N" H 4300 3700 50  0001 L BNN
F 3 "" H 4300 3700 50  0001 L BNN
	1    4300 3700
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x24_Female J1
U 1 1 60B4579F
P 1450 3350
F 0 "J1" H 1478 3326 50  0000 L CNN
F 1 "Conn_01x24_Female" H 1478 3235 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x24_P2.54mm_Vertical" H 1450 3350 50  0001 C CNN
F 3 "~" H 1450 3350 50  0001 C CNN
	1    1450 3350
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x24_Female J2
U 1 1 60B470C3
P 2550 3400
F 0 "J2" H 2578 3376 50  0000 L CNN
F 1 "Conn_01x24_Female" H 2578 3285 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x24_P2.54mm_Vertical" H 2550 3400 50  0001 C CNN
F 3 "~" H 2550 3400 50  0001 C CNN
	1    2550 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 850  5500 850 
Wire Wire Line
	5500 850  5500 2900
Wire Wire Line
	5500 2900 5000 2900
Wire Wire Line
	5500 2900 5500 4650
Connection ~ 5500 2900
Wire Wire Line
	5350 3000 5000 3000
Wire Wire Line
	5350 3000 5350 950 
Wire Wire Line
	5350 950  5000 950 
Wire Wire Line
	5000 4400 5300 4400
Wire Wire Line
	5300 4400 5300 2350
Wire Wire Line
	5300 2350 5000 2350
Wire Wire Line
	3600 3200 2950 3200
Wire Wire Line
	2950 3200 2950 1150
Wire Wire Line
	2950 1150 3600 1150
$Comp
L Connector:Conn_01x04_Female J0
U 1 1 60B4FCFD
P 1850 600
F 0 "J0" V 1788 312 50  0000 R CNN
F 1 "Conn_01x04_Female" V 1697 312 50  0000 R CNN
F 2 "Molex:7708461" H 1850 600 50  0001 C CNN
F 3 "~" H 1850 600 50  0001 C CNN
	1    1850 600 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3650 900  3650 550 
Wire Wire Line
	3650 550  5300 550 
Wire Wire Line
	5300 550  5300 2350
Connection ~ 5300 2350
Wire Wire Line
	5350 950  5350 500 
Wire Wire Line
	5350 500  3050 500 
Wire Wire Line
	3050 500  3050 950 
Connection ~ 5350 950 
Wire Wire Line
	1250 2250 1250 1700
Wire Wire Line
	1250 1700 1850 1700
Wire Wire Line
	1850 1700 1850 1150
Wire Wire Line
	1250 3650 1900 3650
Wire Wire Line
	1900 3650 1900 4650
Wire Wire Line
	1900 4650 5500 4650
Wire Wire Line
	1250 2350 1900 2350
Wire Wire Line
	1900 2350 1900 1350
Wire Wire Line
	1900 1350 3600 1350
Wire Wire Line
	1250 2450 1950 2450
Wire Wire Line
	1950 2450 1950 1450
Wire Wire Line
	1950 1450 3600 1450
Wire Wire Line
	3600 1550 2000 1550
Wire Wire Line
	2000 2550 1250 2550
Wire Wire Line
	2000 1550 2000 2550
Wire Wire Line
	1250 2650 2050 2650
Wire Wire Line
	2050 2650 2050 1650
Wire Wire Line
	2050 1650 3600 1650
Wire Wire Line
	5000 1350 4150 1350
Wire Wire Line
	4150 1350 4150 1700
Wire Wire Line
	4150 1700 2100 1700
Wire Wire Line
	2100 1700 2100 2750
Wire Wire Line
	2100 2750 1250 2750
Wire Wire Line
	1250 2850 2150 2850
Wire Wire Line
	2150 2850 2150 1750
Wire Wire Line
	2150 1750 4200 1750
Wire Wire Line
	4200 1750 4200 1450
Wire Wire Line
	4200 1450 5000 1450
Wire Wire Line
	5000 1550 4250 1550
Wire Wire Line
	4250 1550 4250 1800
Wire Wire Line
	4250 1800 2200 1800
Wire Wire Line
	2200 2950 1250 2950
Wire Wire Line
	2200 1800 2200 2950
Wire Wire Line
	1250 3050 2250 3050
Wire Wire Line
	2250 3050 2250 2200
Wire Wire Line
	2250 2200 4300 2200
Wire Wire Line
	4300 2200 4300 1650
Wire Wire Line
	4300 1650 5000 1650
Wire Wire Line
	1250 3150 2750 3150
Wire Wire Line
	2750 3150 2750 3400
Wire Wire Line
	2750 3400 3600 3400
Wire Wire Line
	3600 3500 2700 3500
Wire Wire Line
	2700 3500 2700 3250
Wire Wire Line
	2700 3250 1250 3250
Wire Wire Line
	1250 3350 2650 3350
Wire Wire Line
	2650 3350 2650 3600
Wire Wire Line
	2650 3600 3600 3600
Wire Wire Line
	3600 3700 2600 3700
Wire Wire Line
	2600 3700 2600 3450
Wire Wire Line
	5000 3400 3950 3400
Wire Wire Line
	3950 3400 3950 3750
Wire Wire Line
	3950 3750 2300 3750
Wire Wire Line
	2300 3750 2300 3550
Wire Wire Line
	2300 3550 1250 3550
Wire Wire Line
	4000 3850 4000 3500
Wire Wire Line
	4000 3500 5000 3500
Wire Wire Line
	2350 3500 2200 3500
Wire Wire Line
	2200 3500 2200 3850
Wire Wire Line
	2200 3850 4000 3850
Wire Wire Line
	2600 3450 1250 3450
Wire Wire Line
	2350 3400 2100 3400
Wire Wire Line
	2100 3400 2100 3950
Wire Wire Line
	2100 3950 4050 3950
Wire Wire Line
	4050 3950 4050 3600
Wire Wire Line
	4050 3600 5000 3600
Wire Wire Line
	5000 3700 4100 3700
Wire Wire Line
	4100 3700 4100 4050
Wire Wire Line
	4100 4050 2050 4050
Wire Wire Line
	2050 4050 2050 3300
Wire Wire Line
	2050 3300 2350 3300
$Comp
L Connector:Conn_01x04_Male J3
U 1 1 60C3C4C0
P 6200 850
F 0 "J3" H 6308 1131 50  0000 C CNN
F 1 "Conn_01x04_Male" H 6308 1040 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 6200 850 50  0001 C CNN
F 3 "~" H 6200 850 50  0001 C CNN
	1    6200 850 
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J4
U 1 1 60C3E792
P 6200 1400
F 0 "J4" H 6308 1681 50  0000 C CNN
F 1 "Conn_01x04_Male" H 6308 1590 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 6200 1400 50  0001 C CNN
F 3 "~" H 6200 1400 50  0001 C CNN
	1    6200 1400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J5
U 1 1 60C3F5B3
P 6200 1950
F 0 "J5" H 6308 2231 50  0000 C CNN
F 1 "Conn_01x04_Male" H 6308 2140 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 6200 1950 50  0001 C CNN
F 3 "~" H 6200 1950 50  0001 C CNN
	1    6200 1950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J6
U 1 1 60C5BA68
P 6200 2500
F 0 "J6" H 6308 2781 50  0000 C CNN
F 1 "Conn_01x04_Male" H 6308 2690 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 6200 2500 50  0001 C CNN
F 3 "~" H 6200 2500 50  0001 C CNN
	1    6200 2500
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J11
U 1 1 60C67820
P 3600 5500
F 0 "J11" H 3708 5781 50  0000 C CNN
F 1 "Conn_01x04_Male" H 3708 5690 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 3600 5500 50  0001 C CNN
F 3 "~" H 3600 5500 50  0001 C CNN
	1    3600 5500
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J12
U 1 1 60C67826
P 3600 6050
F 0 "J12" H 3708 6331 50  0000 C CNN
F 1 "Conn_01x04_Male" H 3708 6240 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 3600 6050 50  0001 C CNN
F 3 "~" H 3600 6050 50  0001 C CNN
	1    3600 6050
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J13
U 1 1 60C6782C
P 3600 6600
F 0 "J13" H 3708 6881 50  0000 C CNN
F 1 "Conn_01x04_Male" H 3708 6790 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 3600 6600 50  0001 C CNN
F 3 "~" H 3600 6600 50  0001 C CNN
	1    3600 6600
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J14
U 1 1 60C67832
P 3600 7150
F 0 "J14" H 3708 7431 50  0000 C CNN
F 1 "Conn_01x04_Male" H 3708 7340 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 3600 7150 50  0001 C CNN
F 3 "~" H 3600 7150 50  0001 C CNN
	1    3600 7150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J15
U 1 1 60C6B71A
P 4900 5450
F 0 "J15" H 5008 5731 50  0000 C CNN
F 1 "Conn_01x04_Male" H 5008 5640 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 4900 5450 50  0001 C CNN
F 3 "~" H 4900 5450 50  0001 C CNN
	1    4900 5450
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J16
U 1 1 60C6B720
P 4900 6000
F 0 "J16" H 5008 6281 50  0000 C CNN
F 1 "Conn_01x04_Male" H 5008 6190 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 4900 6000 50  0001 C CNN
F 3 "~" H 4900 6000 50  0001 C CNN
	1    4900 6000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J17
U 1 1 60C6B726
P 4900 6550
F 0 "J17" H 5008 6831 50  0000 C CNN
F 1 "Conn_01x04_Male" H 5008 6740 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 4900 6550 50  0001 C CNN
F 3 "~" H 4900 6550 50  0001 C CNN
	1    4900 6550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J18
U 1 1 60C6B72C
P 4900 7100
F 0 "J18" H 5008 7381 50  0000 C CNN
F 1 "Conn_01x04_Male" H 5008 7290 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 4900 7100 50  0001 C CNN
F 3 "~" H 4900 7100 50  0001 C CNN
	1    4900 7100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J7
U 1 1 60C7298C
P 6200 3050
F 0 "J7" H 6308 3331 50  0000 C CNN
F 1 "Conn_01x04_Male" H 6308 3240 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 6200 3050 50  0001 C CNN
F 3 "~" H 6200 3050 50  0001 C CNN
	1    6200 3050
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J8
U 1 1 60C72992
P 6200 3600
F 0 "J8" H 6308 3881 50  0000 C CNN
F 1 "Conn_01x04_Male" H 6308 3790 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 6200 3600 50  0001 C CNN
F 3 "~" H 6200 3600 50  0001 C CNN
	1    6200 3600
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J9
U 1 1 60C72998
P 6200 4150
F 0 "J9" H 6308 4431 50  0000 C CNN
F 1 "Conn_01x04_Male" H 6308 4340 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 6200 4150 50  0001 C CNN
F 3 "~" H 6200 4150 50  0001 C CNN
	1    6200 4150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J10
U 1 1 60C7299E
P 6200 4700
F 0 "J10" H 6308 4981 50  0000 C CNN
F 1 "Conn_01x04_Male" H 6308 4890 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 6200 4700 50  0001 C CNN
F 3 "~" H 6200 4700 50  0001 C CNN
	1    6200 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 1850 4500 1850
Wire Wire Line
	4500 1850 4500 1700
Wire Wire Line
	4500 1700 5750 1700
Wire Wire Line
	5750 850  6400 850 
Wire Wire Line
	5750 850  5750 1700
Wire Wire Line
	6400 1400 5850 1400
Wire Wire Line
	5850 1400 5850 1750
Wire Wire Line
	5850 1750 4350 1750
Wire Wire Line
	4350 1750 4350 1950
Wire Wire Line
	4350 1950 3600 1950
Wire Wire Line
	3600 2050 4400 2050
Wire Wire Line
	4400 2050 4400 1800
Wire Wire Line
	4400 1800 5850 1800
Wire Wire Line
	5850 1800 5850 1950
Wire Wire Line
	5850 1950 6400 1950
Wire Wire Line
	6400 2500 3900 2500
Wire Wire Line
	3900 2500 3900 2150
Wire Wire Line
	3900 2150 3600 2150
Wire Wire Line
	5000 1850 5750 1850
Wire Wire Line
	5750 1850 5750 3050
Wire Wire Line
	5750 3050 6400 3050
Wire Wire Line
	5000 1950 5800 1950
Wire Wire Line
	5800 1950 5800 3600
Wire Wire Line
	5800 3600 6400 3600
Wire Wire Line
	5000 2050 5850 2050
Wire Wire Line
	5850 2050 5850 4150
Wire Wire Line
	5850 4150 6400 4150
Wire Wire Line
	5000 2150 5900 2150
Wire Wire Line
	5900 2150 5900 4700
Wire Wire Line
	5900 4700 6400 4700
Wire Wire Line
	3600 3900 4150 3900
Wire Wire Line
	4150 3900 4150 5500
Wire Wire Line
	4150 5500 3800 5500
Wire Wire Line
	3600 4000 4200 4000
Wire Wire Line
	4200 6050 3800 6050
Wire Wire Line
	4200 4000 4200 6050
Wire Wire Line
	3600 4100 4250 4100
Wire Wire Line
	4250 4100 4250 6600
Wire Wire Line
	4250 6600 3800 6600
Wire Wire Line
	3600 4200 4300 4200
Wire Wire Line
	4300 4200 4300 7150
Wire Wire Line
	4300 7150 3800 7150
Wire Wire Line
	4350 3900 4350 5450
Wire Wire Line
	4350 5450 5100 5450
Wire Wire Line
	4350 3900 5000 3900
Wire Wire Line
	5000 4000 4400 4000
Wire Wire Line
	4400 4000 4400 6000
Wire Wire Line
	4400 6000 5100 6000
Wire Wire Line
	5000 4100 4450 4100
Wire Wire Line
	4450 4100 4450 6550
Wire Wire Line
	4450 6550 5100 6550
Wire Wire Line
	5000 4200 4500 4200
Wire Wire Line
	4500 4200 4500 7100
Wire Wire Line
	4500 7100 5100 7100
Wire Wire Line
	3800 5400 4050 5400
Wire Wire Line
	4050 5400 4050 5950
Wire Wire Line
	4050 5950 3800 5950
Wire Wire Line
	4050 5950 4050 6500
Wire Wire Line
	4050 6500 3800 6500
Connection ~ 4050 5950
Wire Wire Line
	4050 6500 4050 7050
Wire Wire Line
	4050 7050 3800 7050
Connection ~ 4050 6500
Wire Wire Line
	4050 7050 4050 7500
Wire Wire Line
	4050 7500 1100 7500
Wire Wire Line
	1100 900  1100 7500
Connection ~ 4050 7050
Wire Wire Line
	3800 6800 4000 6800
Wire Wire Line
	4000 7350 3800 7350
Wire Wire Line
	4000 6800 4000 6250
Wire Wire Line
	4000 6250 3800 6250
Connection ~ 4000 6800
Wire Wire Line
	4000 6250 4000 5700
Wire Wire Line
	4000 5700 3800 5700
Connection ~ 4000 6250
Wire Wire Line
	5100 7300 5450 7300
Wire Wire Line
	5450 7300 5450 6750
Wire Wire Line
	5450 6750 5100 6750
Wire Wire Line
	5450 6750 5450 6200
Wire Wire Line
	5450 6200 5100 6200
Connection ~ 5450 6750
Wire Wire Line
	5450 6200 5450 5650
Wire Wire Line
	5450 5650 5100 5650
Connection ~ 5450 6200
Wire Wire Line
	5100 5350 5650 5350
Wire Wire Line
	5650 5350 5650 5900
Wire Wire Line
	5650 5900 5100 5900
Wire Wire Line
	5650 5900 5650 6450
Wire Wire Line
	5650 6450 5100 6450
Connection ~ 5650 5900
Wire Wire Line
	5650 6450 5650 7000
Wire Wire Line
	5650 7000 5100 7000
Connection ~ 5650 6450
Wire Wire Line
	5650 7000 5650 7500
Connection ~ 5650 7000
Connection ~ 4050 7500
Wire Wire Line
	5450 7300 5450 7700
Wire Wire Line
	5450 7700 4000 7700
Wire Wire Line
	4000 6800 4000 7350
Connection ~ 5450 7300
Connection ~ 4000 7350
Wire Wire Line
	4000 7350 4000 7700
Wire Wire Line
	4000 7700 950  7700
Wire Wire Line
	950  1150 950  7700
Connection ~ 4000 7700
Wire Wire Line
	5450 7700 6950 7700
Wire Wire Line
	6950 1050 6400 1050
Connection ~ 5450 7700
Wire Wire Line
	6400 750  7200 750 
Wire Wire Line
	4050 7500 5650 7500
Connection ~ 5650 7500
Wire Wire Line
	5650 7500 7200 7500
Wire Wire Line
	6400 1600 6950 1600
Connection ~ 6950 1600
Wire Wire Line
	6950 1600 6950 1050
Wire Wire Line
	6400 1850 7200 1850
Connection ~ 7200 1850
Wire Wire Line
	7200 1850 7200 2400
Wire Wire Line
	6400 1300 7200 1300
Wire Wire Line
	7200 750  7200 1300
Connection ~ 7200 1300
Wire Wire Line
	7200 1300 7200 1850
Wire Wire Line
	6400 2150 6950 2150
Connection ~ 6950 2150
Wire Wire Line
	6950 2150 6950 1600
Wire Wire Line
	6400 2400 7200 2400
Connection ~ 7200 2400
Wire Wire Line
	7200 2400 7200 2950
Wire Wire Line
	6400 2700 6950 2700
Wire Wire Line
	6950 2150 6950 2700
Connection ~ 6950 2700
Wire Wire Line
	6400 3250 6950 3250
Wire Wire Line
	6950 2700 6950 3250
Connection ~ 6950 3250
Wire Wire Line
	6950 3250 6950 3800
Wire Wire Line
	6400 2950 7200 2950
Connection ~ 7200 2950
Wire Wire Line
	7200 2950 7200 3500
Wire Wire Line
	6400 3500 7200 3500
Connection ~ 7200 3500
Wire Wire Line
	6400 3800 6950 3800
Connection ~ 6950 3800
Wire Wire Line
	7200 3500 7200 4050
Wire Wire Line
	6950 3800 6950 4350
Wire Wire Line
	6400 4050 7200 4050
Connection ~ 7200 4050
Wire Wire Line
	7200 4050 7200 4600
Wire Wire Line
	6400 4350 6950 4350
Connection ~ 6950 4350
Wire Wire Line
	6400 4600 7200 4600
Connection ~ 7200 4600
Wire Wire Line
	7200 4600 7200 7500
Wire Wire Line
	6400 4900 6950 4900
Wire Wire Line
	6950 4350 6950 4900
Connection ~ 6950 4900
Wire Wire Line
	6950 4900 6950 7700
Wire Wire Line
	3050 950  2050 950 
Wire Wire Line
	1100 900  2050 900 
Wire Wire Line
	2050 800  2050 900 
Connection ~ 2050 900 
Wire Wire Line
	2050 900  2050 950 
Wire Wire Line
	1950 1150 1950 1100
Wire Wire Line
	950  1150 1850 1150
Connection ~ 1850 1150
Wire Wire Line
	1850 1150 1950 1150
Wire Wire Line
	3650 900  3450 900 
Wire Wire Line
	3450 900  3450 1100
Wire Wire Line
	3450 1100 1950 1100
Connection ~ 1950 1100
Wire Wire Line
	1950 1100 1950 800 
$EndSCHEMATC
