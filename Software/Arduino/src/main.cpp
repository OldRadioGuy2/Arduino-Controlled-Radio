/*
Software Controlled Radio - Arduino Main

This is the main entry point for the Arduino code. It's derived from the 8735 
test code (SI4735_01_POC.cpp) and library written by Ricardo Lima Caratti (Nov 2019).

   The table below shows the Si4735 and Arduino Pro Mini pin connections 
    
    | Si4735 pin      |  Arduino Pin  |
    | ----------------| ------------  |
    | RESET (pin 15)  |     2 (was 12)|
    | SDIO (pin 18)   |     A4        |
    | CLK (pin 17)   |     A5         |

*/

#include <Arduino.h>

#include <SI4735.h>

#define RESET_PIN 2

#define AM_FUNCTION 1
#define FM_FUNCTION 0

// Stub for now

void setup()
{
}

void loop()
{
}