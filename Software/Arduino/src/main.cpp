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


#include "arduino_radio.h"
#include "commands.h"

#define RESET_PIN 2

SI4735 rx;

#define CMD_BUF_SIZE 40
char cmd_buffer[CMD_BUF_SIZE];

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
  } 

    Serial.print("The Si473X I2C address is 0x");
    Serial.println(si4735Addr, HEX);
    rx.setup(RESET_PIN, 0); // FM_FUNCTION);
    // rx.setup(RESET_PIN, -1, 1, SI473X_ANALOG_AUDIO);
    // Starts defaul radio function and band (FM; from 84 to 108 MHz; 103.9 MHz; step 100kHz)
}

const command command_list []= {
    {"SF", & set_freq },    // Set Frequency: SF,float_frequency (KHz)
    {"SB", & set_band },    // Set Band: SB,float_lower_limit, float_upper_limit 
    {"SV", & set_volume },  // write the configuration
    {"EN", & enable_feature },    // turn on a feature
    {"DS", & disable_feature },   // turn off a feature
    {"WR", & save_cfg },    // write the configuration
    {"GF", & get_freq },    // Get Current Frequency: GF. Returns float frequency in KHz
    {"CP", & read_Cap }     // read the analog Cap
};

const char * process_cmd_line(void)
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

void print_help(void)
{
    unsigned int i = 0;
    Serial.write( "Commands are :\n" );
    do
    {
        Serial.write( command_list[i].cmd );
        i ++;
        if ( i >= sizeof(command_list) / sizeof(command))
            break;
        Serial.write( ", " );
    } while (1);
    Serial.write( "\n" );
}

void loop(void)
{
    int cmd_in = 0; // start with empty buffer
     CHAR curBand = NUM_BANDS;
    UCHAR curVol = 255;
    UINT currentFrequency = 0;
    BOOL first_set_band = false;

    load_config();
    print_help();

    do  {
        UINT desiredFrequency;

        desiredFrequency = globalConfig.frequency[ (int)globalConfig.band ];

        if (curBand != globalConfig.band) 
        {
            switch (curBand = globalConfig.band) {
                case BAND_AM:
                    Serial.print( "Setting AM " );
                    rx.setAM(520, 1750, desiredFrequency, 10);
                    rx.setSeekAmLimits(520, 1750);
                    rx.setSeekAmSpacing(10); // spacing 10kHz
                    break;
                default:
                    curBand = globalConfig.band = BAND_FM;
                case BAND_FM:
                    Serial.print( "Setting FM " );
                    rx.setFM(8400, 10800, desiredFrequency, 20);
                    rx.setSeekFmSpacing(2);
                    break;
                case BAND_SSB:
                    Serial.print( "Setting SSB " );
                    rx.setAM(100, 30000, desiredFrequency, 5);
                    rx.setSeekAmLimits(100, 30000);   // Range for seeking.
                    rx.setSeekAmSpacing(1); // spacing 1kHz
                    break;
            }
            Serial.println( desiredFrequency );
            delay(500);
            first_set_band = true;
            currentFrequency = desiredFrequency;
        } else        
            currentFrequency = rx.getFrequency();
        if ((currentFrequency != desiredFrequency) &&
            (first_set_band == true))
        {
            char cur_dir = 2, flip_count = 0;

            Serial.print( "Tuning to " );
            Serial.print( desiredFrequency );
            do  {
                if (5 < flip_count)
                {
                    Serial.print( " failed" );
                    break;
                }
                if (currentFrequency < desiredFrequency)
                {
                    rx.frequencyUp();
                    if (1 != cur_dir)
                        flip_count ++;
                    cur_dir = 1;
                } else {
                    rx.frequencyDown();
                    if (0 != cur_dir)
                        flip_count ++;
                    cur_dir = 0;
                }
                currentFrequency = rx.getFrequency();
            } while (currentFrequency != desiredFrequency);
            Serial.println(".");
        }

        if (curVol != globalConfig.volume)
        {
            rx.setVolume(curVol = globalConfig.volume);
            Serial.print("Setting volume ");
            Serial.println(curVol);
        }

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
        if (globalConfig.featureEn[FEATURE_BAND_SW]) {
            // get_band_switch()
        }
        if (globalConfig.featureEn[FEATURE_FREQ_CAP]) {
            // Get Frequency
        }
        if (globalConfig.featureEn[FEATURE_VOLUME]) {
            // Get Volume
        }
        if (globalConfig.featureEn[FEATURE_DISPLAY]) {
            // update the display
        }
    } while (1);
} 

#endif  // #ifdef BUILD_APPLICATION - whole file
