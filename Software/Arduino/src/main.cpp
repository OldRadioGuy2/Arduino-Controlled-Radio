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

#if BUILD_GUI_LIB
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
# define TFT_RST  4
# define TFT_DC   5
# define TFT_CS   6
# define TFT_MOSI 7
# define TFT_MISO 8
# define TFT_CLK  9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
#endif

#if BUILD_RADIO
# define RESET_PIN 2
/* single global instance of the Radio control library class */
SI4735 rx;
#endif

#define CMD_BUF_SIZE 40
char cmd_buffer[CMD_BUF_SIZE];

/* Arduino defined entry point.
 * do some initialization */
void setup(void)
{
  Serial.begin(9600);

#if BUILD_RADIO
  pinMode( RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, HIGH);
#endif

  pinMode( triggerPin, OUTPUT);     // output to trigger 555 timer
  pinMode( pulseInPin, INPUT);      // pulse input
  digitalWrite(triggerPin, HIGH);
  
  Serial.println("Arduino Controlled Radio.");
#if BUILD_GUI_LIB
  tft.begin();
#endif
#if BUILD_RADIO
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
#endif
}

const command command_list []= {
    {"SF", & set_freq },    // Set Frequency: SF,float_frequency (KHz)
    {"SB", & set_band },    // Set Band: SB,float_lower_limit, float_upper_limit 
    {"SV", & set_volume },  // write the configuration
    {"EN", & enable_feature },    // turn on a feature
    {"DS", & disable_feature },   // turn off a feature
    {"WR", & save_cfg },    // write the configuration
    {"GF", & get_freq },    // Get Current Frequency: GF. Returns float frequency in KHz
#if BUILD_GUI_LIB
    {"RO", &  screen_rotate },
#endif
    {"CP", & read_Cap }     // read the analog Cap
};
const char szOn[] = "On";
const char szOff[] = "Off";

void print_help(void)
{
    unsigned int i = 0;
    Serial.write( "Commands are : " );
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

const char * process_cmd_line(void)
{
    unsigned int i = 0;
    if ('?' == cmd_buffer[0]) {
        print_help();
        return "";
    }
    do  {
        const command * cPtr = & command_list[i];
        if ((cPtr->cmd[0] == cmd_buffer[0]) &&
            (cPtr->cmd[1] == cmd_buffer[1]) )
            return cPtr->processor(cmd_buffer);
        i ++;
    } while ( i < sizeof(command_list) / sizeof(command));
    return " not found";    // " -1";
}

#if BUILD_GUI_LIB
# define MY_TEXT_NUM_STEPS    5
 UINT  dispFreq = 999;
 uint8_t curRotate = 255;
 void myText(int line);
 int dbgText(int line);
#endif

/* Arduino defined entry point, like main ()
 * don't return */
void loop(void)
{
    int cmd_in = 0; // start with empty buffer
#if BUILD_GUI_LIB
    uint8_t chRd;
    uint8_t scr_line = 0;
    uint8_t scr_need_up = 0;
#endif
#if BUILD_RADIO
    CHAR curBand = NUM_BANDS;
    UCHAR curVol = 255;
    UINT currentFrequency = 0;
    BOOL first_set_band = false;
#endif
    load_config();

    Serial.print("Read Frequency Cap: ");
    Serial.println( (globalConfig.featureEn[FEATURE_FREQ_CAP]) ? szOn : szOff);
    Serial.print("Read Analog Volume: ");
    Serial.println( (globalConfig.featureEn[FEATURE_VOLUME]) ? szOn : szOff);
    Serial.print("Read Band Switch: ");
    Serial.println( (globalConfig.featureEn[FEATURE_BAND_SW]) ? szOn : szOff);
    Serial.print("Write Display: ");
    Serial.println( (globalConfig.featureEn[FEATURE_DISPLAY]) ? szOn : szOff);

    print_help();

#if BUILD_GUI_LIB
    chRd = tft.readcommand8(ILI9341_RDMODE);
    Serial.print("DisplayPwrMd: 0x"); Serial.println(chRd, HEX);

    chRd = tft.readcommand8(ILI9341_RDMADCTL);
    Serial.print(" MADCTL Mode: 0x"); Serial.println(chRd, HEX);

    chRd = tft.readcommand8(ILI9341_RDPIXFMT);
    Serial.print("Pixel Format: 0x"); Serial.println(chRd, HEX);

    chRd = tft.readcommand8(ILI9341_RDIMGFMT);
    Serial.print("Image Format: 0x"); Serial.println(chRd, HEX);

    chRd = tft.readcommand8(ILI9341_RDSELFDIAG);
    Serial.print("  Self Diag : 0x"); Serial.println(chRd, HEX); 
#endif

    do  {
        UINT desiredFrequency = globalConfig.frequency[ (int)globalConfig.band ];
#if BUILD_RADIO
        /* control the radio if globalConfig has changed */
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
#endif

        /* service the serial port - command line interface */
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

        /* Implement the features if enabled in globalConfig */

        /* Feature 3:
         * change AM/FM Band based on a digital or analog input */
        if (globalConfig.featureEn[FEATURE_BAND_SW]) {
            int pinA1;  // get_band_switch()
            char newBand;
#if 1
            pinMode(digitalBandSwitch, INPUT);
            pinA1 = digitalRead(digitalBandSwitch);
            if (pinA1)
                newBand = BAND_FM;
            else
                newBand = BAND_AM;
#else
            pinA1 = analogRead(analogBandSwitch);
            if (pinA1 > (MAX_ANALOG_VALUE / 2))
                newBand = BAND_FM;
            else
                newBand = BAND_AM;
#endif
            if (globalConfig.band != newBand)
            {
                Serial.print("Band Sw now");
                Serial.println(bandStrings[ (int)newBand]);
                globalConfig.band = newBand;
            }
        }
        /* Feature 1:
         * change frequency based on a digital or analog input */
        if (globalConfig.featureEn[FEATURE_FREQ_CAP]) {
            // Get Frequency
            Serial.println("insert Cap read here.");
        }
        /* Feature 2:
         * change volume based on an analog input */
        if (globalConfig.featureEn[FEATURE_VOLUME]) {
            // Get Volume
            static int lastVolume = -1;
            int pinA0 = analogRead(analogVolumePin);
            if (((pinA0 - lastVolume) > 4) || ((lastVolume - pinA0) > 4)) {
                Serial.print("Analog volume ");
                Serial.println(pinA0);
                lastVolume = pinA0;
            }
            globalConfig.volume = (pinA0 * MAX_VOLUME) / (MAX_ANALOG_VALUE -1);
        }
        /* Feature 4:
         * update a display for output */
#if BUILD_GUI_LIB
        if (globalConfig.featureEn[FEATURE_DISPLAY]) {
            // update the display
# if 1
            if ((curRotate != globalConfig.scrRotate) &&
                (0 == scr_need_up))
            {
                curRotate = globalConfig.scrRotate; // newRotate;
                tft.setRotation(curRotate);
                Serial.print("rotate"); Serial.println(curRotate, DEC); 
                goto set_anyway;
            }
#endif
     if (dispFreq != desiredFrequency)
     {
   set_anyway:
      Serial.print("freq"); Serial.println(desiredFrequency, DEC); 
      dispFreq = desiredFrequency;
      if (2 != scr_need_up)
        scr_need_up ++;
    }

    if (0 != scr_need_up) {
      if (MY_TEXT_NUM_STEPS > scr_line) {
        myText(scr_line);
        scr_line ++;
    } else {
        if (dbgText(scr_line - MY_TEXT_NUM_STEPS))
        {
          scr_line = 0;
# if 1
          if (curRotate != globalConfig.scrRotate) {
            curRotate = globalConfig.scrRotate;
           tft.setRotation(curRotate);
        }
# endif
          scr_need_up --;
        } else
          scr_line ++;
      }
    }
        }
#endif
    } while (1);
} 

#if BUILD_GUI_LIB
void myText(int line)
{
  switch (line) {
    case 0:
      tft.fillScreen(ILI9341_BLACK);
      tft.setCursor(0, 0);
      break;
    case 1:
      tft.setTextColor(ILI9341_WHITE);
      tft.setTextSize(3);  tft.println("Lyle Monster!");
      tft.println();
      break;
    case 2:
      tft.setTextColor(ILI9341_YELLOW);
      tft.setTextSize(5);
      tft.print( (curRotate & 1) ? "Freq:" : "Fq:");
      if (BAND_FM == globalConfig.band) {
        tft.print(dispFreq / 100);
        tft.print('.');
        tft.println((dispFreq / 10) % 10);
      } else 
        tft.println(dispFreq);
      tft.setTextSize(3);
      if (0 == (curRotate & 1))
          tft.println();
      break;
    case 3:
      tft.setTextColor(ILI9341_GREEN);
      tft.setTextSize(4);  tft.print("W1ZTL ");
      if (0 == (curRotate & 1))  tft.println();
      break;
    case 4:
      tft.setTextSize(3);  tft.println("Workshop");
      if (0 != (curRotate & 1))  tft.println();
      tft.setTextSize(1);
      break;
  }
}

int dbgText(int line)
{
  char buildLine[34];
  int i, j = 0;

  i = line * 16;
    do {
      buildLine[j] =  (uint8_t) i;
      j ++; i ++;
      buildLine[j] = ' ';
      j ++;
    } while (32 > j);
    buildLine[j] = '\0';
  tft.println(buildLine);
  if (curRotate & 1)
   return (line >= (8 -1));
 return (line >= (16 -1));
}
#endif

#endif  // #ifdef BUILD_APPLICATION - whole file
