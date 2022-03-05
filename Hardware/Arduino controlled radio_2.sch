EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
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
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 602F06C3
P 3350 3100
F 0 "A1" H 2925 4075 50  0000 C CNN
F 1 "Arduino_BLE_Nano" H 3975 4125 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 3350 3100 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 3350 3100 50  0001 C CNN
	1    3350 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C5
U 1 1 60304AD4
P 7500 2825
F 0 "C5" V 7271 2825 50  0000 C CNN
F 1 "22nf" V 7362 2825 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7500 2825 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 7500 2825 50  0001 C CNN
	1    7500 2825
	0    1    1    0   
$EndComp
Wire Wire Line
	7100 1875 7100 2825
Wire Wire Line
	7800 3200 8000 3200
Wire Wire Line
	8000 3200 8000 2825
Wire Wire Line
	8000 2825 7600 2825
Wire Wire Line
	7400 2825 7300 2825
Connection ~ 7300 2825
Wire Wire Line
	7300 2825 7300 2900
$Comp
L Device:C_Small C4
U 1 1 6030D9B7
P 6800 2825
F 0 "C4" V 6571 2825 50  0000 C CNN
F 1 "100nf" V 6662 2825 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 6800 2825 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 6800 2825 50  0001 C CNN
	1    6800 2825
	0    1    1    0   
$EndComp
$Comp
L power:GNDREF #PWR04
U 1 1 6030E97E
P 6525 2900
F 0 "#PWR04" H 6525 2650 50  0001 C CNN
F 1 "GNDREF" H 6530 2727 50  0000 C CNN
F 2 "" H 6525 2900 50  0001 C CNN
F 3 "" H 6525 2900 50  0001 C CNN
	1    6525 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 2825 6900 2825
Connection ~ 7100 2825
Wire Wire Line
	7100 2825 7100 2900
Wire Wire Line
	6700 2825 6525 2825
Wire Wire Line
	6525 2825 6525 2900
$Comp
L power:GNDREF #PWR05
U 1 1 60312DD6
P 7100 4650
F 0 "#PWR05" H 7100 4400 50  0001 C CNN
F 1 "GNDREF" H 7105 4477 50  0001 C CNN
F 2 "" H 7100 4650 50  0001 C CNN
F 3 "" H 7100 4650 50  0001 C CNN
	1    7100 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 4500 7100 4575
Connection ~ 7100 4575
Wire Wire Line
	7100 4575 7100 4650
$Comp
L Device:C_Small C3
U 1 1 60314D5D
P 6025 3900
F 0 "C3" V 5975 3975 50  0000 C CNN
F 1 "22pf" V 6125 3775 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 6025 3900 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 6025 3900 50  0001 C CNN
	1    6025 3900
	0    1    1    0   
$EndComp
$Comp
L Device:Crystal_Small Y1
U 1 1 6031610B
P 6375 3800
F 0 "Y1" V 6329 3888 50  0000 L CNN
F 1 "32768KHz" V 6575 3550 50  0000 L CNN
F 2 "Crystal:Crystal_SMD_3215-2Pin_3.2x1.5mm" H 6375 3800 50  0001 C CNN
F 3 "CM7V-T1A-32.768KHZ-6PF-20PPM-TA-QC" H 6375 3800 50  0001 C CNN
	1    6375 3800
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 60320CBB
P 6025 3700
F 0 "C2" V 5975 3800 50  0000 C CNN
F 1 "22pf" V 6125 3575 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 6025 3700 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 6025 3700 50  0001 C CNN
	1    6025 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	6600 3700 6375 3700
Wire Wire Line
	6375 3700 6125 3700
Connection ~ 6375 3700
Wire Wire Line
	6600 3900 6375 3900
Wire Wire Line
	6125 3900 6375 3900
Connection ~ 6375 3900
Wire Wire Line
	5925 3700 5800 3700
Wire Wire Line
	5800 4575 7100 4575
$Comp
L Device:R_Small_US R4
U 1 1 6032F4FD
P 5425 3200
F 0 "R4" V 5250 3200 50  0000 C CNN
F 1 "10K" V 5325 3200 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 5425 3200 50  0001 C CNN
F 3 "https://www.nteinc.com/resistor_web/pdf/100mW.pdf" H 5425 3200 50  0001 C CNN
	1    5425 3200
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C1
U 1 1 60330457
P 5800 3350
F 0 "C1" H 5892 3396 50  0000 L CNN
F 1 "10nF" H 5525 3350 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 5800 3350 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 5800 3350 50  0001 C CNN
	1    5800 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3700 5800 3900
Wire Wire Line
	5925 3900 5800 3900
Connection ~ 5800 3900
Wire Wire Line
	5800 3900 5800 4575
Wire Wire Line
	5525 3200 5800 3200
Wire Wire Line
	5800 3250 5800 3200
Wire Wire Line
	5800 3200 6600 3200
Wire Wire Line
	5800 3450 5800 3700
Connection ~ 5800 3700
Wire Wire Line
	7800 3600 7975 3600
$Comp
L Device:C_Small C7
U 1 1 603112B5
P 8100 4700
F 0 "C7" H 8192 4746 50  0000 L CNN
F 1 "6.8pF" H 8192 4655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 8100 4700 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 8100 4700 50  0001 C CNN
	1    8100 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:Ferrite_Bead_Small FB1
U 1 1 60312601
P 8325 4500
F 0 "FB1" V 8200 4425 50  0000 C CNN
F 1 "Ferrite_Bead_Small" V 8179 4500 50  0001 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric_Pad1.05x1.20mm_HandSolder" V 8255 4500 50  0001 C CNN
F 3 "https://www.digikey.com/en/products/detail/fair-rite-products-corp/2743021447/8594323" H 8325 4500 50  0001 C CNN
	1    8325 4500
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_Coaxial J7
U 1 1 603159BC
P 9475 4500
F 0 "J7" H 9575 4475 50  0000 L CNN
F 1 "Conn_Coaxial" H 9575 4384 50  0001 L CNN
F 2 "Arduino controlled radio:CONN_1-1337543-0" H 9475 4500 50  0001 C CNN
F 3 "~https://www.digikey.com/en/products/detail/te-connectivity-amp-connectors/1-1337543-0/1755940" H 9475 4500 50  0001 C CNN
	1    9475 4500
	1    0    0    -1  
$EndComp
$Comp
L Device:L L1
U 1 1 60316E5B
P 8350 3900
F 0 "L1" V 8425 3900 50  0000 C CNN
F 1 "10nH" V 8300 3900 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8350 3900 50  0001 C CNN
F 3 "https://www.digikey.com/en/products/detail/bourns-inc/CW105550A-10NJ/9826815" H 8350 3900 50  0001 C CNN
	1    8350 3900
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C8
U 1 1 6031A8E4
P 8575 4100
F 0 "C8" H 8667 4146 50  0000 L CNN
F 1 "3.3pF" H 8667 4055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 8575 4100 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 8575 4100 50  0001 C CNN
	1    8575 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C6
U 1 1 6031B000
P 8100 4100
F 0 "C6" H 8192 4146 50  0000 L CNN
F 1 "3.3pF" H 8192 4055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 8100 4100 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 8100 4100 50  0001 C CNN
	1    8100 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 3900 8100 3900
Wire Wire Line
	8500 3900 8575 3900
Wire Wire Line
	8100 4000 8100 3900
Connection ~ 8100 3900
Wire Wire Line
	8100 3900 8200 3900
Wire Wire Line
	8575 4000 8575 3900
Connection ~ 8575 3900
Wire Wire Line
	8575 3900 9000 3900
Wire Wire Line
	8575 4200 8575 4250
Wire Wire Line
	8575 4250 8100 4250
Wire Wire Line
	7875 4250 7875 4100
Wire Wire Line
	7875 4100 7800 4100
Wire Wire Line
	8100 4200 8100 4250
Connection ~ 8100 4250
Wire Wire Line
	8100 4250 7875 4250
Wire Wire Line
	7800 4000 7950 4000
Wire Wire Line
	7950 4000 7950 4500
Wire Wire Line
	7950 4500 8100 4500
Wire Wire Line
	8100 4600 8100 4500
Connection ~ 8100 4500
Wire Wire Line
	8100 4500 8225 4500
Wire Wire Line
	8425 4500 8800 4500
Wire Wire Line
	9450 4100 9450 4250
Wire Wire Line
	9450 4250 8575 4250
Connection ~ 8575 4250
Wire Wire Line
	9475 4700 9475 5075
Wire Wire Line
	8800 4600 8800 4500
Connection ~ 8800 4500
Wire Wire Line
	8800 4500 9275 4500
Connection ~ 9000 3900
Wire Wire Line
	9000 3900 9250 3900
Wire Wire Line
	8900 5000 8900 5175
Wire Wire Line
	8900 5175 7650 5175
Wire Wire Line
	7650 5175 7650 4575
Wire Wire Line
	9475 5075 8100 5075
Wire Wire Line
	7875 5075 7875 4250
Connection ~ 7875 4250
Wire Wire Line
	8100 4800 8100 5075
Connection ~ 8100 5075
Wire Wire Line
	8100 5075 7875 5075
Wire Wire Line
	9000 3900 9000 4600
Wire Wire Line
	5225 1725 5225 3200
Wire Wire Line
	3450 1875 3450 2100
$Comp
L power:GNDREF #PWR03
U 1 1 604854FD
P 3450 4225
F 0 "#PWR03" H 3450 3975 50  0001 C CNN
F 1 "GNDREF" H 3455 4052 50  0000 C CNN
F 2 "" H 3450 4225 50  0001 C CNN
F 3 "" H 3450 4225 50  0001 C CNN
	1    3450 4225
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 4100 3450 4175
Wire Wire Line
	3350 4100 3350 4175
Wire Wire Line
	3350 4175 3450 4175
Connection ~ 3450 4175
Wire Wire Line
	3450 4175 3450 4225
Wire Wire Line
	2650 1725 2650 3100
$Comp
L Device:R_Small_US R1
U 1 1 604D5495
P 2250 3700
F 0 "R1" V 2200 3750 50  0000 L CNN
F 1 "10k" V 2175 3500 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 2250 3700 50  0001 C CNN
F 3 "https://www.nteinc.com/resistor_web/pdf/100mW.pdf" H 2250 3700 50  0001 C CNN
	1    2250 3700
	0    1    1    0   
$EndComp
Text Notes 725  3925 0    39   ~ 0
Volume Control +5
Text Notes 725  4025 0    39   ~ 0
Volume Control In
Text Notes 725  4125 0    39   ~ 0
Volume Control Gnd
Text Notes 725  3725 0    39   ~ 0
Tuning Control Drive
Text Notes 725  3825 0    39   ~ 0
Tuning Control Gnd
$Comp
L Connector:Screw_Terminal_01x06 J4
U 1 1 603957B8
P 1450 3900
F 0 "J4" H 1450 3450 50  0000 C CNN
F 1 "Screw_Terminal_01x06" H 1368 4226 50  0001 C CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-6_1x06_P2.54mm_Horizontal" H 1450 3900 50  0001 C CNN
F 3 "https://www.digikey.com/en/products/detail/on-shore-technology-inc/OSTVN06A150/1588866" H 1450 3900 50  0001 C CNN
	1    1450 3900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3850 3800 3950 3800
Wire Wire Line
	3950 3800 3950 4500
$Comp
L power:GNDREF #PWR02
U 1 1 603DDEAB
P 1750 5275
F 0 "#PWR02" H 1750 5025 50  0001 C CNN
F 1 "GNDREF" H 1755 5102 50  0001 C CNN
F 2 "" H 1750 5275 50  0001 C CNN
F 3 "" H 1750 5275 50  0001 C CNN
	1    1750 5275
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 4000 1950 4600
Wire Wire Line
	4050 4600 4050 3700
Wire Wire Line
	4050 3700 3850 3700
Wire Wire Line
	1650 3800 1750 3800
Wire Wire Line
	1750 3800 1750 4100
Wire Wire Line
	1650 4100 1750 4100
Connection ~ 1750 4100
Wire Wire Line
	1750 4100 1750 4200
Wire Wire Line
	1650 4200 1750 4200
Connection ~ 1750 4200
Wire Wire Line
	1650 3900 1850 3900
$Comp
L Connector:Screw_Terminal_01x06 J3
U 1 1 6040539B
P 1450 3250
F 0 "J3" H 1575 3525 50  0000 C CNN
F 1 "Screw_Terminal_01x06" H 1368 3576 50  0001 C CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-6_1x06_P2.54mm_Horizontal" H 1450 3250 50  0001 C CNN
F 3 "https://www.digikey.com/en/products/detail/on-shore-technology-inc/OSTVN06A150/1588866" H 1450 3250 50  0001 C CNN
	1    1450 3250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1650 3550 1750 3550
Wire Wire Line
	1750 3550 1750 3800
Connection ~ 1750 3800
Wire Wire Line
	2850 3600 2250 3600
Wire Wire Line
	2250 3600 2250 3450
Wire Wire Line
	2850 3500 2350 3500
Wire Wire Line
	2350 3500 2350 3350
Wire Wire Line
	2850 3400 2450 3400
Wire Wire Line
	2450 3400 2450 3250
Wire Wire Line
	2850 3300 2550 3300
Wire Wire Line
	2550 3300 2550 3150
Wire Wire Line
	2850 3100 2650 3100
Wire Wire Line
	2850 3200 2600 3200
Wire Wire Line
	2600 3200 2600 3050
Text Notes 1300 3075 0    39   ~ 0
D6
Text Notes 1250 3575 0    39   ~ 0
GND
Wire Wire Line
	3250 2100 3250 2025
$Comp
L power:GNDREF #PWR01
U 1 1 604AF81E
P 1625 2150
F 0 "#PWR01" H 1625 1900 50  0001 C CNN
F 1 "GNDREF" H 1630 1977 50  0001 C CNN
F 2 "" H 1625 2150 50  0001 C CNN
F 3 "" H 1625 2150 50  0001 C CNN
	1    1625 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1525 2075 1625 2075
Wire Wire Line
	1625 2075 1625 2150
NoConn ~ 6600 4100
NoConn ~ 7800 3400
NoConn ~ 6600 3400
NoConn ~ 3850 2500
NoConn ~ 3850 2900
NoConn ~ 3850 3100
NoConn ~ 3850 3200
NoConn ~ 2850 3000
NoConn ~ 2850 2700
NoConn ~ 7800 3700
$Comp
L power:+5V #PWR06
U 1 1 60563EA2
P 7300 1375
F 0 "#PWR06" H 7300 1225 50  0001 C CNN
F 1 "+5V" H 7325 1525 50  0000 C CNN
F 2 "" H 7300 1375 50  0001 C CNN
F 3 "" H 7300 1375 50  0001 C CNN
	1    7300 1375
	1    0    0    -1  
$EndComp
NoConn ~ 2850 2900
NoConn ~ 2850 2800
NoConn ~ 6600 4000
NoConn ~ 3850 2600
$Comp
L Power_Protection:SP0502BAHT D1
U 1 1 6034B058
P 8900 4800
F 0 "D1" H 9100 5000 50  0000 L CNN
F 1 "SP0502BAHT" H 8975 4625 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9125 4750 50  0001 L CNN
F 3 "https://www.digikey.com/en/products/detail/semtech-corporation/RCLAMP3552T.TNT/7941072" H 9025 4925 50  0001 C CNN
	1    8900 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 3100 4800 3225
Wire Wire Line
	4800 3425 4800 3500
Wire Wire Line
	5025 3100 5025 1875
Connection ~ 5025 3100
Wire Wire Line
	4800 3100 5025 3100
Wire Wire Line
	5025 3225 5025 3100
Wire Wire Line
	5025 3425 5025 3600
$Comp
L Device:R_Small_US R3
U 1 1 603001E8
P 5025 3325
F 0 "R3" H 4900 3450 50  0000 L CNN
F 1 "4.7K" H 5075 3325 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 5025 3325 50  0001 C CNN
F 3 "https://www.nteinc.com/resistor_web/pdf/100mW.pdf" H 5025 3325 50  0001 C CNN
	1    5025 3325
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R2
U 1 1 602FFA60
P 4800 3325
F 0 "R2" H 4675 3450 50  0000 L CNN
F 1 "4.7K" H 4575 3325 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 4800 3325 50  0001 C CNN
F 3 "https://www.nteinc.com/resistor_web/pdf/100mW.pdf" H 4800 3325 50  0001 C CNN
	1    4800 3325
	1    0    0    -1  
$EndComp
Connection ~ 5800 3200
NoConn ~ 2850 2500
NoConn ~ 2850 2600
$Comp
L Connector:Jack-DC J1
U 1 1 604AE4B7
P 1225 1975
F 0 "J1" H 1282 2300 50  0000 C CNN
F 1 "Jack-DC" H 1282 2209 50  0000 C CNN
F 2 "Arduino controlled radio:CUI_PJ-202B" H 1275 1935 50  0001 C CNN
F 3 "https://www.digikey.com/en/products/detail/cui-devices/PJ-202B/252008" H 1275 1935 50  0001 C CNN
	1    1225 1975
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x06 J5
U 1 1 605085BA
P 1450 4800
F 0 "J5" H 1450 5125 50  0000 C CNN
F 1 "Screw_Terminal_01x06" H 1368 5126 50  0001 C CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-6_1x06_P2.54mm_Horizontal" H 1450 4800 50  0001 C CNN
F 3 "https://www.digikey.com/en/products/detail/on-shore-technology-inc/OSTVN06A150/1588866" H 1450 4800 50  0001 C CNN
	1    1450 4800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3850 3400 4150 3400
Wire Wire Line
	4150 3400 4150 4700
Wire Wire Line
	3850 3300 4250 3300
Wire Wire Line
	4250 3300 4250 5000
Wire Wire Line
	1750 4200 1750 4800
Wire Wire Line
	1650 4800 1750 4800
Connection ~ 1750 4800
Wire Wire Line
	1750 4800 1750 5100
Wire Wire Line
	1650 5100 1750 5100
Connection ~ 1750 5100
Wire Wire Line
	1750 5100 1750 5275
Wire Wire Line
	7300 1575 7300 2825
Wire Wire Line
	7300 1575 7300 1375
Connection ~ 7300 1575
Wire Wire Line
	1850 1575 1850 3900
Wire Wire Line
	1525 1875 1750 1875
Wire Wire Line
	1850 1575 3550 1575
Wire Wire Line
	1650 3050 2600 3050
Wire Wire Line
	1650 3150 2550 3150
Wire Wire Line
	1650 3250 2450 3250
Wire Wire Line
	1650 3350 2350 3350
Wire Wire Line
	1650 3450 2250 3450
Wire Wire Line
	1650 4000 1950 4000
Wire Wire Line
	1650 3700 2050 3700
Wire Wire Line
	1650 4700 4150 4700
Wire Wire Line
	1650 5000 4250 5000
Wire Wire Line
	1850 3900 1850 4600
Wire Wire Line
	1850 4900 1650 4900
Connection ~ 1850 3900
Wire Wire Line
	1650 4600 1850 4600
Connection ~ 1850 4600
Wire Wire Line
	1850 4600 1850 4900
Wire Wire Line
	1950 4600 4050 4600
Connection ~ 2050 3700
Wire Wire Line
	2050 3700 2150 3700
Wire Wire Line
	2050 3700 2050 3800
Wire Wire Line
	2350 3700 2850 3700
Wire Wire Line
	2050 3800 2850 3800
Connection ~ 2050 3800
Wire Wire Line
	2050 3800 2050 4500
Wire Wire Line
	2050 4500 3950 4500
Text Notes 800  4625 0    39   ~ 0
Band Switch +5
Text Notes 800  4725 0    39   ~ 0
Band Switch Sense
Text Notes 800  4825 0    39   ~ 0
Band Switch GND
NoConn ~ -650 4675
NoConn ~ 6875 5700
Wire Wire Line
	5225 3200 5325 3200
Wire Wire Line
	2650 1725 5225 1725
Connection ~ 4800 3500
Wire Wire Line
	4800 3500 6600 3500
Connection ~ 5025 1875
Wire Wire Line
	5025 1875 7100 1875
Connection ~ 5025 3600
Wire Wire Line
	5025 3600 6600 3600
Wire Wire Line
	3850 3500 4800 3500
Wire Wire Line
	3450 1875 5025 1875
Wire Wire Line
	3850 3600 5025 3600
$Sheet
S 9650 2650 500  175 
U 6074E751
F0 "Sheet6074E750" 50
F1 "Audio Amplifier.sch" 50
$EndSheet
Text GLabel 2250 1875 2    50   Input ~ 0
12V
Text GLabel 7975 3600 2    50   Input ~ 0
RChan
Text GLabel 7975 3500 2    50   Input ~ 0
LChan
Wire Wire Line
	7800 3500 7975 3500
$Comp
L Connector:Conn_Coaxial J6
U 1 1 6097EAEC
P 9450 3900
F 0 "J6" H 9550 3875 50  0000 L CNN
F 1 "Conn_Coaxial" H 9550 3784 50  0001 L CNN
F 2 "Arduino controlled radio:CONN_1-1337543-0" H 9450 3900 50  0001 C CNN
F 3 "~https://www.digikey.com/en/products/detail/te-connectivity-amp-connectors/1-1337543-0/1755940" H 9450 3900 50  0001 C CNN
	1    9450 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 1875 2125 1875
Wire Wire Line
	2125 1875 2125 2025
Wire Wire Line
	2125 2025 3250 2025
$Comp
L RF_AM_FM:Si4735-D60-GU U1
U 1 1 602F28C3
P 7200 3700
F 0 "U1" H 6900 4450 50  0000 C CNN
F 1 "Si4735-D60-GU" H 7650 4450 50  0000 C CNN
F 2 "Package_SO:SSOP-24_3.9x8.7mm_P0.635mm" H 7450 3000 50  0001 L CNN
F 3 "http://www.silabs.com/Support%20Documents/TechnicalDocs/Si4730-31-34-35-D60.pdf" H 7250 2700 50  0001 C CNN
	1    7200 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 4575 7300 4575
Wire Wire Line
	7300 4500 7300 4575
Connection ~ 7300 4575
Wire Wire Line
	7300 4575 7650 4575
Wire Wire Line
	3550 1575 3550 2100
Connection ~ 3550 1575
Wire Wire Line
	3550 1575 7300 1575
$Comp
L Connector:Screw_Terminal_01x06 J2
U 1 1 6045555B
P 1450 2600
F 0 "J2" H 1575 2900 50  0000 C CNN
F 1 "Screw_Terminal_01x06" H 1368 2926 50  0001 C CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-6_1x06_P2.54mm_Horizontal" H 1450 2600 50  0001 C CNN
F 3 "https://www.digikey.com/en/products/detail/on-shore-technology-inc/OSTVN06A150/1588866" H 1450 2600 50  0001 C CNN
	1    1450 2600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1650 2400 1750 2400
Wire Wire Line
	1750 2400 1750 1875
Text GLabel 2225 2500 2    50   Input ~ 0
12V
$Comp
L Device:CP1_Small C18
U 1 1 6048AE81
P 2125 2725
AR Path="/6048AE81" Ref="C18"  Part="1" 
AR Path="/6074E751/6048AE81" Ref="C?"  Part="1" 
F 0 "C18" V 2225 2725 50  0000 C CNN
F 1 "100uF 16V" V 2025 2725 50  0000 C CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x7.7" H 2125 2725 50  0001 C CNN
F 3 "https://surgecomponents.com/content/pdfs/capacitors/VE.pdf" H 2125 2725 50  0001 C CNN
	1    2125 2725
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR017
U 1 1 6049CEDC
P 2125 2900
F 0 "#PWR017" H 2125 2650 50  0001 C CNN
F 1 "GNDREF" H 2130 2727 50  0001 C CNN
F 2 "" H 2125 2900 50  0001 C CNN
F 3 "" H 2125 2900 50  0001 C CNN
	1    2125 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 2500 2125 2500
Wire Wire Line
	2125 2625 2125 2600
Connection ~ 2125 2500
Wire Wire Line
	2125 2500 2225 2500
Wire Wire Line
	2125 2825 2125 2900
Wire Wire Line
	1650 2700 1725 2700
Wire Wire Line
	1725 2700 1725 2900
Wire Wire Line
	1725 2900 1650 2900
Wire Wire Line
	1650 2600 1800 2600
Connection ~ 2125 2600
Wire Wire Line
	2125 2600 2125 2500
Wire Wire Line
	1650 2800 1800 2800
Wire Wire Line
	1800 2800 1800 2600
Connection ~ 1800 2600
Wire Wire Line
	1800 2600 2125 2600
Wire Wire Line
	1725 2900 2125 2900
Connection ~ 1725 2900
Connection ~ 2125 2900
Text Notes 925  2425 0    39   ~ 0
On/Off Sw Pwr\n
Text Notes 850  2525 0    39   ~ 0
On/Off Sw Return
Text Notes 1225 2625 0    39   ~ 0
+12V\n
Text Notes 1225 2825 0    39   ~ 0
+12V\n
Text Notes 1275 2725 0    39   ~ 0
Gnd\n
Text Notes 1275 2925 0    39   ~ 0
Gnd\n
Text Notes 1300 3175 0    39   ~ 0
D7
Text Notes 1300 3275 0    39   ~ 0
D8
Text Notes 1300 3375 0    39   ~ 0
D9
Text Notes 1275 3475 0    39   ~ 0
D10
$EndSCHEMATC
