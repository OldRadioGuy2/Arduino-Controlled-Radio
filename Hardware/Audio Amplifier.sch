EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 2350 2875 0    50   Input ~ 0
RChan
Text GLabel 2350 3700 0    50   Input ~ 0
LChan
$Comp
L Amplifier_Operational:LM358 U3
U 1 1 62665F1B
P 3725 2775
F 0 "U3" H 3425 3075 50  0000 C CNN
F 1 "TL082" H 3875 2950 50  0000 C CNN
F 2 "Arduino controlled radio:TL082CDR" H 3725 2775 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 3725 2775 50  0001 C CNN
	1    3725 2775
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 6266C752
P 3000 2875
AR Path="/6266C752" Ref="R?"  Part="1" 
AR Path="/6074E751/6266C752" Ref="R11"  Part="1" 
F 0 "R11" V 3175 2875 50  0000 C CNN
F 1 "22K" V 3100 2875 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3000 2875 50  0001 C CNN
F 3 "https://www.nteinc.com/resistor_web/pdf/100mW.pdf" H 3000 2875 50  0001 C CNN
	1    3000 2875
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 6266CF35
P 3000 3700
AR Path="/6266CF35" Ref="R?"  Part="1" 
AR Path="/6074E751/6266CF35" Ref="R12"  Part="1" 
F 0 "R12" V 2795 3700 50  0000 C CNN
F 1 "22K" V 2886 3700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3000 3700 50  0001 C CNN
F 3 "https://www.nteinc.com/resistor_web/pdf/100mW.pdf" H 3000 3700 50  0001 C CNN
	1    3000 3700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 6266D525
P 3150 2450
AR Path="/6266D525" Ref="R?"  Part="1" 
AR Path="/6074E751/6266D525" Ref="R13"  Part="1" 
F 0 "R13" H 3300 2425 50  0000 C CNN
F 1 "22K" H 3300 2500 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3150 2450 50  0001 C CNN
F 3 "https://www.nteinc.com/resistor_web/pdf/100mW.pdf" H 3150 2450 50  0001 C CNN
	1    3150 2450
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 626B7B70
P 2800 4250
AR Path="/626B7B70" Ref="C?"  Part="1" 
AR Path="/6074E751/626B7B70" Ref="C12"  Part="1" 
F 0 "C12" H 2975 4200 50  0000 C CNN
F 1 ".1uF" H 2975 4275 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2800 4250 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 2800 4250 50  0001 C CNN
	1    2800 4250
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 626B9283
P 3800 3150
AR Path="/626B9283" Ref="R?"  Part="1" 
AR Path="/6074E751/626B9283" Ref="R15"  Part="1" 
F 0 "R15" V 3900 3150 50  0000 C CNN
F 1 "22K" V 3700 3150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3800 3150 50  0001 C CNN
F 3 "https://www.nteinc.com/resistor_web/pdf/100mW.pdf" H 3800 3150 50  0001 C CNN
	1    3800 3150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 626C27F6
P 3800 3900
AR Path="/626C27F6" Ref="R?"  Part="1" 
AR Path="/6074E751/626C27F6" Ref="R16"  Part="1" 
F 0 "R16" V 3900 3900 50  0000 C CNN
F 1 "22K" V 3686 3900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3800 3900 50  0001 C CNN
F 3 "https://www.nteinc.com/resistor_web/pdf/100mW.pdf" H 3800 3900 50  0001 C CNN
	1    3800 3900
	0    -1   -1   0   
$EndComp
$Comp
L power:GNDREF #PWR?
U 1 1 626DE4E1
P 3150 4525
AR Path="/626DE4E1" Ref="#PWR?"  Part="1" 
AR Path="/6074E751/626DE4E1" Ref="#PWR024"  Part="1" 
F 0 "#PWR024" H 3150 4275 50  0001 C CNN
F 1 "GNDREF" H 3155 4352 50  0001 C CNN
F 2 "" H 3150 4525 50  0001 C CNN
F 3 "" H 3150 4525 50  0001 C CNN
	1    3150 4525
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 626F3FC6
P 2575 2875
AR Path="/626F3FC6" Ref="C?"  Part="1" 
AR Path="/6074E751/626F3FC6" Ref="C10"  Part="1" 
F 0 "C10" V 2346 2875 50  0000 C CNN
F 1 "1uF" V 2437 2875 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2575 2875 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 2575 2875 50  0001 C CNN
	1    2575 2875
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 626F4AB3
P 2600 3700
AR Path="/626F4AB3" Ref="C?"  Part="1" 
AR Path="/6074E751/626F4AB3" Ref="C11"  Part="1" 
F 0 "C11" V 2371 3700 50  0000 C CNN
F 1 "1uF" V 2462 3700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2600 3700 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 2600 3700 50  0001 C CNN
	1    2600 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	2675 2875 2900 2875
Wire Wire Line
	2700 3700 2900 3700
$Comp
L Amplifier_Operational:LM358 U3
U 2 1 62728267
P 3700 3600
F 0 "U3" H 3375 3850 50  0000 C CNN
F 1 "TL082" H 3900 3775 50  0000 C CNN
F 2 "" H 3700 3600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 3700 3600 50  0001 C CNN
	2    3700 3600
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM358 U3
U 3 1 627324D5
P 3725 2775
F 0 "U3" H 3683 2821 50  0001 L CNN
F 1 "LM358" H 3683 2730 50  0001 L CNN
F 2 "" H 3725 2775 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 3725 2775 50  0001 C CNN
	3    3725 2775
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR025
U 1 1 6273C6C9
P 3625 2225
F 0 "#PWR025" H 3625 2075 50  0001 C CNN
F 1 "+12V" H 3640 2398 50  0000 C CNN
F 2 "" H 3625 2225 50  0001 C CNN
F 3 "" H 3625 2225 50  0001 C CNN
	1    3625 2225
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 62754ACC
P 3150 4250
AR Path="/62754ACC" Ref="R?"  Part="1" 
AR Path="/6074E751/62754ACC" Ref="R14"  Part="1" 
F 0 "R14" H 3000 4200 50  0000 C CNN
F 1 "22K" H 3000 4300 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3150 4250 50  0001 C CNN
F 3 "https://www.nteinc.com/resistor_web/pdf/100mW.pdf" H 3150 4250 50  0001 C CNN
	1    3150 4250
	-1   0    0    1   
$EndComp
Wire Wire Line
	4000 3600 4175 3600
Wire Wire Line
	4025 2775 4175 2775
Wire Wire Line
	4175 2775 4175 3150
Wire Wire Line
	4175 3150 3900 3150
Connection ~ 4175 2775
Wire Wire Line
	4175 2775 4275 2775
Wire Wire Line
	3700 3150 3375 3150
Wire Wire Line
	3375 3150 3375 2875
Wire Wire Line
	3375 2875 3425 2875
Wire Wire Line
	3375 2875 3100 2875
Connection ~ 3375 2875
Wire Wire Line
	3400 3700 3350 3700
Wire Wire Line
	4175 3600 4175 3900
Wire Wire Line
	4175 3900 3900 3900
Connection ~ 4175 3600
Wire Wire Line
	4175 3600 4300 3600
Wire Wire Line
	3700 3900 3350 3900
Wire Wire Line
	3350 3900 3350 3700
Connection ~ 3350 3700
Wire Wire Line
	3350 3700 3100 3700
Wire Wire Line
	3150 2550 3150 2675
Wire Wire Line
	3150 4100 2800 4100
Wire Wire Line
	2800 4100 2800 4150
Connection ~ 3150 4100
Wire Wire Line
	3150 4100 3150 4150
Wire Wire Line
	3150 4350 3150 4450
Wire Wire Line
	2800 4350 2800 4450
Wire Wire Line
	2800 4450 3150 4450
Connection ~ 3150 4450
Wire Wire Line
	3150 4450 3150 4525
Wire Wire Line
	3625 2475 3625 2275
Wire Wire Line
	3150 2350 3150 2275
Wire Wire Line
	3150 2275 3625 2275
Connection ~ 3625 2275
Wire Wire Line
	3425 2675 3150 2675
Connection ~ 3150 2675
Wire Wire Line
	3150 2675 3150 3500
Wire Wire Line
	3400 3500 3150 3500
Wire Wire Line
	3150 3500 3150 4100
$Comp
L Device:R_Small_US R?
U 1 1 6280734A
P 5075 3600
AR Path="/6280734A" Ref="R?"  Part="1" 
AR Path="/6074E751/6280734A" Ref="R17"  Part="1" 
F 0 "R17" V 5175 3675 50  0000 C CNN
F 1 "1K" V 5175 3550 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5075 3600 50  0001 C CNN
F 3 "https://www.nteinc.com/resistor_web/pdf/100mW.pdf" H 5075 3600 50  0001 C CNN
	1    5075 3600
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 62807C47
P 5075 3850
AR Path="/62807C47" Ref="R?"  Part="1" 
AR Path="/6074E751/62807C47" Ref="R18"  Part="1" 
F 0 "R18" V 5175 3850 50  0000 C CNN
F 1 "1K" V 4975 3850 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5075 3850 50  0001 C CNN
F 3 "https://www.nteinc.com/resistor_web/pdf/100mW.pdf" H 5075 3850 50  0001 C CNN
	1    5075 3850
	0    -1   -1   0   
$EndComp
$Comp
L Arduino~Controlled~Radio:SJ1-3525NG J7
U 1 1 6282733C
P 5475 3125
F 0 "J7" H 5500 2675 50  0000 R CNN
F 1 "SJ1-3525NG" V 7925 4250 50  0001 R CNN
F 2 "Arduino controlled radio:CUI_SJ1-3525NG" H 5475 3125 50  0001 L BNN
F 3 "" H 5475 3125 50  0001 L BNN
F 4 "1.01" H 5475 3125 50  0001 L BNN "PARTREV"
F 5 "CUI" H 5475 3125 50  0001 L BNN "MANUFACTURER"
F 6 "Manufacturer recommendation" H 5475 3125 50  0001 L BNN "STANDARD"
	1    5475 3125
	-1   0    0    1   
$EndComp
Wire Wire Line
	4475 2775 4625 2775
Wire Wire Line
	4625 2775 4625 2925
Wire Wire Line
	4625 2925 4875 2925
Wire Wire Line
	4625 3600 4625 3225
Wire Wire Line
	4625 3225 4875 3225
Wire Wire Line
	4875 3125 4775 3125
Wire Wire Line
	4700 3025 4875 3025
$Comp
L Connector:Conn_Coaxial J8
U 1 1 6296D3E0
P 7375 3750
F 0 "J8" H 7475 3725 50  0000 L CNN
F 1 "Speaker" H 7475 3634 50  0000 L CNN
F 2 "Arduino controlled radio:CUI_RCJ-045" H 7375 3750 50  0001 C CNN
F 3 " ~" H 7375 3750 50  0001 C CNN
	1    7375 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 3025 4700 3850
Wire Wire Line
	4700 3850 4975 3850
Wire Wire Line
	4775 3125 4775 3600
Wire Wire Line
	4775 3600 4975 3600
Wire Wire Line
	5175 3600 5450 3600
Wire Wire Line
	5175 3850 5450 3850
Wire Wire Line
	4500 3600 4625 3600
$Comp
L power:GNDREF #PWR027
U 1 1 62A452E0
P 4875 3400
F 0 "#PWR027" H 4875 3150 50  0001 C CNN
F 1 "GNDREF" H 4880 3227 50  0001 C CNN
F 2 "" H 4875 3400 50  0001 C CNN
F 3 "" H 4875 3400 50  0001 C CNN
	1    4875 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4875 3325 4875 3400
Wire Wire Line
	2475 2875 2350 2875
Wire Wire Line
	2500 3700 2350 3700
Connection ~ 3150 3500
$Comp
L power:GNDREF #PWR?
U 1 1 622F45BF
P 3625 3225
AR Path="/622F45BF" Ref="#PWR?"  Part="1" 
AR Path="/6074E751/622F45BF" Ref="#PWR026"  Part="1" 
F 0 "#PWR026" H 3625 2975 50  0001 C CNN
F 1 "GNDREF" H 3630 3052 50  0001 C CNN
F 2 "" H 3625 3225 50  0001 C CNN
F 3 "" H 3625 3225 50  0001 C CNN
	1    3625 3225
	1    0    0    -1  
$EndComp
Wire Wire Line
	3625 3075 3625 3225
$Comp
L Device:C_Small C?
U 1 1 62286222
P 4375 2775
AR Path="/62286222" Ref="C?"  Part="1" 
AR Path="/6074E751/62286222" Ref="C13"  Part="1" 
F 0 "C13" V 4146 2775 50  0000 C CNN
F 1 "10uF" V 4237 2775 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4375 2775 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 4375 2775 50  0001 C CNN
	1    4375 2775
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 6228E17B
P 4400 3600
AR Path="/6228E17B" Ref="C?"  Part="1" 
AR Path="/6074E751/6228E17B" Ref="C14"  Part="1" 
F 0 "C14" V 4171 3600 50  0000 C CNN
F 1 "10uF" V 4262 3600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4400 3600 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 4400 3600 50  0001 C CNN
	1    4400 3600
	0    1    1    0   
$EndComp
$Comp
L Arduino~Controlled~Radio:TPA3118AmplifierBoard U4
U 1 1 6233817B
P 6650 3500
F 0 "U4" H 6375 3450 50  0000 C CNN
F 1 "TPA3118AmplifierBoard" H 7075 3450 50  0000 C CNN
F 2 "Arduino controlled radio:TPA3118_Board" H 6650 3500 50  0001 C CNN
F 3 "" H 6650 3500 50  0001 C CNN
	1    6650 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 3600 5450 3750
Wire Wire Line
	6150 3750 5450 3750
Connection ~ 5450 3750
Wire Wire Line
	5450 3750 5450 3850
$Comp
L power:GNDREF #PWR?
U 1 1 62376C06
P 5975 4550
AR Path="/62376C06" Ref="#PWR?"  Part="1" 
AR Path="/6074E751/62376C06" Ref="#PWR028"  Part="1" 
F 0 "#PWR028" H 5975 4300 50  0001 C CNN
F 1 "GNDREF" H 5980 4377 50  0001 C CNN
F 2 "" H 5975 4550 50  0001 C CNN
F 3 "" H 5975 4550 50  0001 C CNN
	1    5975 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5975 4550 5975 4525
Wire Wire Line
	5975 3850 6150 3850
Wire Wire Line
	6550 4525 5975 4525
Connection ~ 5975 4525
Wire Wire Line
	5975 4525 5975 3850
Wire Wire Line
	7175 3750 7000 3750
Wire Wire Line
	7000 3850 7000 3975
Wire Wire Line
	6550 4450 6550 4525
Wire Wire Line
	3625 2275 3625 2225
$Comp
L power:+12V #PWR029
U 1 1 6239123F
P 7125 2900
F 0 "#PWR029" H 7125 2750 50  0001 C CNN
F 1 "+12V" H 7140 3073 50  0000 C CNN
F 2 "" H 7125 2900 50  0001 C CNN
F 3 "" H 7125 2900 50  0001 C CNN
	1    7125 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1_Small C15
U 1 1 623A714F
P 6925 3175
F 0 "C15" H 7016 3221 50  0000 L CNN
F 1 "100uF" H 7016 3130 50  0000 L CNN
F 2 "Capacitor_SMD:C_Elec_6.3x5.4" H 6925 3175 50  0001 C CNN
F 3 "~" H 6925 3175 50  0001 C CNN
	1    6925 3175
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR?
U 1 1 623B24B2
P 7125 3375
AR Path="/623B24B2" Ref="#PWR?"  Part="1" 
AR Path="/6074E751/623B24B2" Ref="#PWR030"  Part="1" 
F 0 "#PWR030" H 7125 3125 50  0001 C CNN
F 1 "GNDREF" H 7130 3202 50  0001 C CNN
F 2 "" H 7125 3375 50  0001 C CNN
F 3 "" H 7125 3375 50  0001 C CNN
	1    7125 3375
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 623B313B
P 7325 3175
AR Path="/623B313B" Ref="C?"  Part="1" 
AR Path="/6074E751/623B313B" Ref="C16"  Part="1" 
F 0 "C16" H 7150 3150 50  0000 C CNN
F 1 ".1 uF" H 7150 3275 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7325 3175 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 7325 3175 50  0001 C CNN
	1    7325 3175
	-1   0    0    1   
$EndComp
Wire Wire Line
	6925 3275 6925 3325
Wire Wire Line
	6925 3325 7125 3325
Wire Wire Line
	7125 3325 7125 3375
Wire Wire Line
	7325 3275 7325 3325
Wire Wire Line
	7325 3325 7125 3325
Connection ~ 7125 3325
Wire Wire Line
	6550 3550 6550 3000
Wire Wire Line
	6550 3000 6925 3000
Wire Wire Line
	6925 3000 6925 3075
Wire Wire Line
	6925 3000 7125 3000
Wire Wire Line
	7325 3000 7325 3075
Connection ~ 6925 3000
Wire Wire Line
	7125 2900 7125 3000
Connection ~ 7125 3000
Wire Wire Line
	7125 3000 7325 3000
Wire Wire Line
	7375 3950 7375 3975
Wire Wire Line
	7000 3975 7375 3975
$EndSCHEMATC
