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

#include "select_build.h"
#ifdef BUILD_APPLICATION

#include <Arduino.h>
#include <SI4735.h>

#include "arduino_radio.h"
#include "commands.h"

#define RESET_PIN 2

#define AM_FUNCTION 1
#define FM_FUNCTION 0
SI4735 rx;
char cmd_buffer[40];
CONFIG * config;


void setup(){
  Serial.begin(9600);
  while(!Serial);

  digitalWrite(RESET_PIN, HIGH);
  
  Serial.println("Arduino Controlled Radio.");
// Look for the Si47XX I2C bus address
  rx.setI2CStandardMode();
  int16_t si4735Addr = rx.getDeviceI2CAddress(RESET_PIN);
  if ( si4735Addr == 0 ) {
    Serial.println("Si473X not found!");
    Serial.flush();
    while (1);
  } else {
    Serial.print("The Si473X I2C address is 0x");
    Serial.println(si4735Addr, HEX);
  }

}

char * process_cmd_line() {
    char * cmd=strtok(cmd_buffer,",");
    unsigned int i;
    for (i=0; i < sizeof(command_list) && strcmp(cmd, command_list[i].cmd) != 0; i++ ) ;
    if ( i < sizeof(command_list) ){
        return command_list[i].processor(cmd_buffer);
    }
    else {
        return (char *) &"-1";
    }
}

void loop()
{
    cmd_buffer[0] = '\0'; //Clear the buffer
    if (Serial.available() >= 2) {
        Serial.readBytesUntil('\n',cmd_buffer,sizeof(cmd_buffer)-1);
        Serial.write(process_cmd_line());
    }
    if (config->use_band_switch) {
        //get_band_switch()
    }
    if (config->use_frequency_cap) {
        //Get Frequency
    }
    if (config->use_volume_ctrl) {
        //Get Volume
    }
    
    
} 

#endif //BUILD_APPLICATION