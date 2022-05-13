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

#define CMD_BUF_SIZE 40
char cmd_buffer[CMD_BUF_SIZE];
CONFIG * config;


void setup()
{
  Serial.begin(9600);
  // while (!Serial);

  pinMode( RESET_PIN, OUTPUT);     // output to trigger 555 timer
  digitalWrite(RESET_PIN, HIGH);

  pinMode( triggerPin, OUTPUT);     // output to trigger 555 timer
  pinMode( pulseInPin, INPUT);      // pulse input
  digitalWrite(triggerPin, HIGH);
  
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

const command command_list []= {
    {"SF", & process_sf },    //Set Frequency: SF,float_frequency (KHz)
    {"SB", & process_sb },    //Set Band: SB,float_lower_limit, float_upper_limit 
    {"GF", & process_gf },      //Get Current Frequency: GF. Returns float frequency in KHz
    {"CP", & read_Cap  }      //Get Current Frequency: GF. Returns float frequency in KHz
};

const char * process_cmd_line()
{
    unsigned int i = 0;
    do  {
        const command * cPtr = & command_list[i];
        if ((cPtr->cmd[0] == cmd_buffer[0]) &&
            (cPtr->cmd[1] == cmd_buffer[1]) )
            return cPtr->processor(cmd_buffer);
        i ++;
    } while ( i < sizeof(command_list) / sizeof(command));
    return " not found";    // " -1";
}

void loop()
{
    int cmd_in = 0; // start with empty buffer
  do  {
    if (Serial.available()) {
        char key = Serial.read();

        if ('\n' == key) {
            cmd_buffer[cmd_in] = '\0';
            Serial.write( process_cmd_line() );
            Serial.print('\n');
            cmd_in = 0;
        } else
        if (0x08 == key) {
            if (1 <= cmd_in) {
                Serial.print('\r');
                cmd_in --;
                cmd_buffer[cmd_in] = '\0';
                if (cmd_in)
                    Serial.write(cmd_buffer, cmd_in);
            }
        } else
        if (('\r' != key) && (0x1B != key) &&
            (CMD_BUF_SIZE -1 > cmd_in) ) {
                cmd_buffer[cmd_in] = key;
                Serial.print(key);
                cmd_in ++;
        }
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
  } while (1);
} 

#endif //BUILD_APPLICATION