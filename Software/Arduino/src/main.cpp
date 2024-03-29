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

#include "display.h"
#endif

#if BUILD_RADIO
# define RESET_PIN 2

const char * const strBandwidthAM[NUM_BW_DEF_AM] = {
    "6", "4", "3", "2", "1", "1.8", "2.5"
};
/* units are KHz for AM bands */
const FREQ_VAL bandwidthAM[NUM_BW_DEF_AM] = {
    6,  4,  3,  2,  1,  1, 1
};
/* and 10's of KHz for FM */
const FREQ_VAL bandwidthFM[NUM_BW_DEF_FM] = {
    0, 11, 8, 6, 4
};

/* single global instance of the Radio control library class */
SI4735 rx;
#endif

#define CMD_BUF_SIZE 40

#if SOFT_SERIAL
# include <SoftwareSerial.h>

SoftwareSerial BLE_Serial (BLE_RxPin, BLE_TxPin);

char ble_cmd_buffer[CMD_BUF_SIZE];
#endif

char dbg_cmd_buffer[CMD_BUF_SIZE];

char fmt_rsp_buffer[RSP_BUF_SIZE];

/* Arduino defined entry point.
 * do some initialization */
void setup(void)
{
  Serial.begin(9600);

#if BUILD_RADIO
  pinMode( RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, HIGH);
#endif

#if SOFT_SERIAL
    pinMode(BLE_RxPin, INPUT);
    pinMode(BLE_TxPin, OUTPUT);

    BLE_Serial.begin (9600);
#endif

  pinMode( triggerPin, OUTPUT);     // output to trigger 555 timer
  pinMode( pulseInPin, INPUT);      // pulse input
  digitalWrite(triggerPin, HIGH);
  
  Serial.println(F("Arduino Controlled Radio."));
#if BUILD_GUI_LIB
  tft.begin();
#endif
#if SOFT_SERIAL
    BLE_Serial.println(F("Hello"));
#endif
#if BUILD_RADIO
// Look for the Si47XX I2C bus address
  rx.setI2CStandardMode();
  int16_t si4735Addr = rx.getDeviceI2CAddress(RESET_PIN);
  if ( si4735Addr == 0 ) {
    Serial.println(F("Si473X not found!"));
    Serial.flush();
    while (1);
  } 

    Serial.print(F("The Si473X I2C address is 0x"));
    Serial.println(si4735Addr, HEX);
    rx.setup(RESET_PIN, 0); // FM_FUNCTION);
    // rx.setup(RESET_PIN, -1, 1, SI473X_ANALOG_AUDIO);
    // Starts defaul radio function and band (FM; from 84 to 108 MHz; 103.9 MHz; step 100kHz)
#endif

/* Analog refrence for A to D */
    // if (globalConfig.featureEn[FEATURE_VOLUME])
    pinMode(analogVolumePin, INPUT);
#if PLATFORM == NANO_ATMEGA_BOARD
    analogReference( DEFAULT );
#endif
#if PLATFORM == NANO_BLE_BOARD
    analogReference( AR_INTERNAL2V4 );
#endif
}

const command command_list []= {
    {"SF", & set_freq },    // Set Frequency: SF,float_frequency (KHz)
    {"SB", & set_band },    // Set Band: SB,float_lower_limit, float_upper_limit 
    {"SV", & set_volume },  // write the configuration
    {"EV", & volume_feature },    // turn on/off analog volume feature
    {"ET", & tuning_feature },   // turn on/off tuning cap feature
    {"EB", & band_sw_feature },    // turn on/off analog band sw feature
    {"ED", & display_feature },   // turn on/off writing display feature
    {"GS", & get_sig_lvl },    // Get Current Frequency: GF. Returns float frequency in KHz
    {"GB", & get_band },    // Get Current Frequency: GF. Returns float frequency in KHz
    {"GV", & get_volume },    // Get Current Frequency: GF. Returns float frequency in KHz
    {"GF", & get_freq },    // Get Current Frequency: GF. Returns float frequency in KHz
    {"WR", & save_cfg },    // write the configuration
    {"MB", & create_band }, // 
    {"DB", & delete_band }, // 
    {"CT", & calibrate_tuner }, // 
    {"CB", & calibrate_band }, // 
    {"CP", & read_Cap }     // read the analog Cap
};
const char szOn[] = "On";
const char szOff[] = "Off";

void print_help(void)
{
    unsigned int i = 0;
    Serial.print( F("Commands are : ") );
    do
    {
        Serial.write( command_list[i].cmd );
        i ++;
        if ( i >= sizeof(command_list) / sizeof(command))
            break;
        Serial.print( F(", ") );
    } while (1);
    Serial.print( F("\n") );
}

CHAR BLE_command = 0;
CHAR cur_Mode = MODE_NOT_VALID;

const char * process_cmd_line(char is_ble)
{
    char * cmd_buffer;
    unsigned int i = 0;
#if SOFT_SERIAL
    if (is_ble)
        cmd_buffer = ble_cmd_buffer;
    else
#endif
        cmd_buffer = dbg_cmd_buffer;

    fmt_rsp_buffer[0] = '\0';
    BLE_command = is_ble;

    if (('?' == cmd_buffer[0]) &&
        (0 == is_ble))
    {
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

CHAR forceBand = 0;
BOOL prev_mode_valid = false;
BOOL mode_is_valid = false;

#if BUILD_GUI_LIB
 UINT  dispFreq = 999;
 uint8_t curRotate = 255;
 void myText(int line);
 int dbgText(int line);
#endif

/* Arduino defined entry point, like main ()
 * don't return */
void loop(void)
{
    int dbg_cmd_in = 0; // start with empty buffer
#if SOFT_SERIAL
    int ble_cmd_in = 0; // start with empty buffer
#endif
    uint8_t chRd;
#if BUILD_GUI_LIB
    uint8_t scr_line = 0;
    uint8_t scr_need_up = 0;
#endif
#if BUILD_RADIO
    CHAR curBand = NUM_BANDS;
    UCHAR curVol = 255;
    UINT currentFrequency = 0;
#endif
    load_config();

    Serial.print(F("Read Frequency Cap: "));
    Serial.println( (globalConfig.featureEn[FEATURE_FREQ_CAP]) ? szOn : szOff);
    chRd = globalConfig.featureEn[FEATURE_VOLUME];
    Serial.print(F("Read Analog Volume: "));
        if ((3 == chRd) || (6 == chRd))
        Serial.println(F("rev-log."));
    else if ((2 == chRd) || (5 == chRd))
        Serial.println(F("log-scale."));
    else if ((1 == chRd) || (4 == chRd))
        Serial.println(F("linear."));
    else
        Serial.println(szOff);
    Serial.print(F("Read Band Switch: "));
    if (globalConfig.featureEn[FEATURE_BAND_SW]) {
        Serial.print( globalConfig.numBandCfg +1 );
        Serial.println( F(" bands.") );
    } else
        Serial.println( szOff );
    Serial.print(F("Write Display: "));
    chRd = globalConfig.featureEn[FEATURE_DISPLAY];
    if (chRd) {
        Serial.print( F("rotate") );
        Serial.println( chRd );
    } else
        Serial.println( szOff );

#if BUILD_GUI_LIB
    chRd = tft.readcommand8(ILI9341_RDMODE);
    Serial.print(F("DisplayPwrMd: 0x")); Serial.println(chRd, HEX);

    chRd = tft.readcommand8(ILI9341_RDMADCTL);
    Serial.print(F(" MADCTL Mode: 0x")); Serial.println(chRd, HEX);

    chRd = tft.readcommand8(ILI9341_RDPIXFMT);
    Serial.print(F("Pixel Format: 0x")); Serial.println(chRd, HEX);

    chRd = tft.readcommand8(ILI9341_RDIMGFMT);
    Serial.print(F("Image Format: 0x")); Serial.println(chRd, HEX);

    chRd = tft.readcommand8(ILI9341_RDSELFDIAG);
    Serial.print(F("  Self Diag : 0x")); Serial.println(chRd, HEX); 
#endif

#if BUILD_RADIO && 1
     curBand = 0;
     do {
        UINT min, max;
        BAND_CFG * bandCfg = & globalConfig.bands[(int)curBand];
        cur_Mode = bandCfg->mode;
        if (NUM_MODES <= cur_Mode)
            cur_Mode = MODE_NOT_VALID;
        if (cur_Mode != MODE_NOT_VALID) {
            min = bandCfg->minFreq;
            max = bandCfg->maxFreq;
            currentFrequency = globalConfig.actFreq[(int)curBand];
            if (MODE_FM == cur_Mode) {
                min /= 10; max /= 10;
                currentFrequency /= 10;
            }
            Serial.print(F("Band"));   Serial.print(curBand + BAND_ONES_OFFSET, DEC);
            Serial.print(modeStrings[ (int)cur_Mode ]);
            Serial.print(F(" from ")); Serial.print(min);
            Serial.print(F(" to "));   Serial.print(max);
            Serial.print(F(" cur "));  Serial.print(currentFrequency);
            Serial.print(F(" bw ")); 
            if (MODE_FM == cur_Mode) {
                if (0 == bandCfg->bw) 
                    Serial.println(F("Auto")); 
                 else Serial.println( bandwidthFM[bandCfg->bw]);
            } else Serial.println(strBandwidthAM[bandCfg->bw]);
        }
        curBand ++;
     } while (curBand < NUM_BANDS);
    Serial.print(F("Active band "));   Serial.print(globalConfig.actBand + BAND_ONES_OFFSET, DEC);
    Serial.print(F(" out of "));   Serial.println(NUM_BANDS, DEC);
#endif
    print_help();

    do {
#if BUILD_RADIO || BUILD_GUI_LIB
        UINT desiredFreq = globalConfig.actFreq[ (int)globalConfig.actBand ];
#endif

#if BUILD_RADIO
        /* control the radio if globalConfig has changed */
        if ((curBand != globalConfig.actBand) || (0 != forceBand))
        {
            BAND_CFG * bandCfg;

            curBand = globalConfig.actBand;
            prev_mode_valid = mode_is_valid;
            mode_is_valid = false;
            if (NUM_BANDS > curBand) {
                bandCfg = & globalConfig.bands[(int)curBand];

                cur_Mode = bandCfg->mode;
                switch (cur_Mode) {
                    case MODE_AM:
                        Serial.print( F("Setting AM ") );
                        rx.setAM(bandCfg->minFreq, bandCfg->maxFreq, desiredFreq, 10);
                        rx.setBandwidth(bandCfg->bw, 1);
                        rx.setSeekAmLimits(bandCfg->minFreq, bandCfg->maxFreq);
                        rx.setSeekAmSpacing(10); // spacing 10kHz
                        goto mode_good;
                    case MODE_FM:
                        Serial.print( F("Setting FM ") );
                        rx.setFM(bandCfg->minFreq, bandCfg->maxFreq, desiredFreq, 20);
                        rx.setSeekFmSpacing(2);
                        goto mode_good;
                    case MODE_SSB:
                        Serial.print( F("Setting SSB ") );
                        rx.setAM(bandCfg->minFreq, bandCfg->maxFreq, desiredFreq, 5);
                        rx.setSeekAmLimits(bandCfg->minFreq, bandCfg->maxFreq);   // Range for seeking.
                        rx.setSeekAmSpacing(1); // spacing 1kHz
                    mode_good:
                        if ((bandCfg->minFreq <= desiredFreq) &&
                            (bandCfg->maxFreq >= desiredFreq)) {
                            mode_is_valid = true;
                            curVol = 0;         // force a volume update when mode is valid
                            break;
                        }
                        Serial.print( F("Freq not valid ") );
                        goto freq_not_valid;
                    case MODE_NOT_VALID:
                    default:
                        Serial.print( F("Mode not valid ") );
                    freq_not_valid:
                        if (prev_mode_valid) {
                            rx.setVolume(0);
                            Serial.println(F("- set vol 0"));
                        }
                        break;
                }
                Serial.println( (MODE_FM == cur_Mode) ? (desiredFreq / 10) : desiredFreq );
                delay(500);
            }
            forceBand = 0;
      //    currentFrequency = desiredFreq;
        } else
            currentFrequency = rx.getFrequency();
        if ((currentFrequency != desiredFreq) &&
            (mode_is_valid == true))
        {
            char cur_dir = 2, flip_count = 0;

            Serial.print( F("Tuning to ") );
            Serial.print( (MODE_FM == cur_Mode) ? (desiredFreq / 10) : desiredFreq );
            do  {
                if (5 < flip_count)
                {
                    Serial.print( F(" - failed at ") );
                    Serial.print( currentFrequency );
                    mode_is_valid = false;
                    break;
                }
                if (currentFrequency < desiredFreq)
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
            } while (currentFrequency != desiredFreq);
            Serial.println(".");
        }

        if (curVol != globalConfig.actVolume)
        {
            rx.setVolume(curVol = globalConfig.actVolume);
            Serial.print(F("Setting volume "));
            Serial.println(curVol);
        }
#endif

        /* service the serial port - command line interface */
#if SOFT_SERIAL
        while (BLE_Serial.available())
        {
            char key = BLE_Serial.read();

            if ( ('\r' == key) || ('\n' == key) )
            {
                const char * resStr;
                ble_cmd_buffer[ble_cmd_in] = '\0';
                resStr = process_cmd_line(1);
                BLE_Serial.print(F("{"));
                BLE_Serial.write( resStr );
                BLE_Serial.write( fmt_rsp_buffer );
                BLE_Serial.print(F("}\n\r"));
                ble_cmd_in = 0;
            } else
            if ( // ('\n' != key) && (0x1B != key) &&
                (CMD_BUF_SIZE -1 > ble_cmd_in) ) {
                    ble_cmd_buffer[ble_cmd_in] = key;
            //      BLE_Serial.print(key);          // Echo !
                    ble_cmd_in ++;
            }
        }
#endif
        while (Serial.available())
        {
            char key = Serial.read();
            if ('\n' == key) {
                const char * resStr;
                dbg_cmd_buffer[dbg_cmd_in] = '\0';
                resStr = process_cmd_line(0);
                Serial.write( resStr );
                Serial.write( fmt_rsp_buffer );
                Serial.print('\n');
                dbg_cmd_in = 0;
            } else
            if (0x08 == key) {
                if (1 <= dbg_cmd_in) {
                    Serial.print('\r');
                    dbg_cmd_in --;
                    dbg_cmd_buffer[dbg_cmd_in] = '\0';
                    if (dbg_cmd_in)
                        Serial.write(dbg_cmd_buffer, dbg_cmd_in);
                }
            } else
            if (('\r' != key) && (0x1B != key) &&
                (CMD_BUF_SIZE -1 > dbg_cmd_in) ) {
                    if (('a' <= key) && ('z' >= key))
                        key -= ('a' - 'A');
                    dbg_cmd_buffer[dbg_cmd_in] = key;
                    Serial.print(key);          // Echo !
                    dbg_cmd_in ++;
            }
        }

        /* Implement the features if enabled in globalConfig */

        /* Feature 3:
         * change AM/FM Band based on a digital or analog input */
        if (globalConfig.featureEn[FEATURE_BAND_SW]) {
            char newBand = 0;
            A2D_VAL pinA1 = analogRead(analogBandSwitch);
            do {
                if (pinA1 < globalConfig.bndSwCal[(int)newBand])
                    break;
                newBand ++;
             } while (globalConfig.numBandCfg > newBand);
             /* ignore a value of zero here */
             if (0 < newBand) {
                newBand --;
                if (globalConfig.actBand != newBand)
                {
                    Serial.print(F("Band Sw now "));
                    Serial.println((int)newBand);
                    globalConfig.actBand = newBand;
                }
             }
        }
        /* Feature 1:
         * change frequency by doing a capacitence/timing measurement */
        if ((globalConfig.featureEn[FEATURE_FREQ_CAP]) &&
            (NUM_BANDS > curBand)) {      // Get cap, calc Frequency
            BAND_CFG * bandCfg = & globalConfig.bands[(int)curBand];
            FREQ_VAL newFreq;
            unsigned long bandFreq, offFreq;
            CAP_RD_VAL shortCnt, diff, tuner = measure_Cap_timing( false );

            bandFreq = bandCfg->maxFreq - bandCfg->minFreq;
            if ( globalConfig.tunerCal[1] > globalConfig.tunerCal[0]) {
                shortCnt = globalConfig.tunerCal[0];
                diff = globalConfig.tunerCal[1] - globalConfig.tunerCal[0];
            } else {
                shortCnt = globalConfig.tunerCal[1];
                diff = globalConfig.tunerCal[0] - globalConfig.tunerCal[1];
            }
            if (tuner > shortCnt)
                tuner -= shortCnt;
            else tuner = 0;
            offFreq = (bandFreq * tuner) / diff;
            if ( globalConfig.tunerCal[1] > globalConfig.tunerCal[0]) {
                newFreq = bandCfg->minFreq + (FREQ_VAL)offFreq;
            } else {
                newFreq = bandCfg->maxFreq - (FREQ_VAL)offFreq;
            }
#if 1
            {
                static UINT saveFrequency = 0;
                newFreq = roundToBandwidth(newFreq);
                if (saveFrequency != newFreq) {
                    Serial.print(F("Cal dif "));
                    Serial.print( diff );
                    Serial.print(F(" tuner "));
                    Serial.print(tuner);

                    Serial.print(F(" New freq "));
                    Serial.print( newFreq );
                    Serial.print(F(" offset "));
                    Serial.println(offFreq);

                    saveFrequency = newFreq;
                }
            }
#endif
#if 0
            currentFrequency = roundToBandwidth(newFrequency);
            if ( globalConfig.actFreq[(int)curBand] != currentFrequency) {
                Serial.print(F("Band Sw now "));
                Serial.println(currentFrequency);
                globalConfig.actFreq[(int)curBand] = roundToBandwidth();
            }
#endif
        }
        /* Feature 2:
         * change volume based on an analog input */
        if (globalConfig.featureEn[FEATURE_VOLUME]) {
            // Get Volume
            int pinA0 = analogRead(analogVolumePin);
            UCHAR newVol;

            switch (globalConfig.featureEn[FEATURE_VOLUME]) {
                case 3:         // opposite log scale
                    pinA0 = (MAX_ANALOG_VALUE - pinA0);
                case 6:         // opposite log scale upside down
                    newVol = MAX_VOLUME - pot_log_scale(pinA0);
                    break;

                case 5:         // log scale upside down
                    pinA0 = (MAX_ANALOG_VALUE - pinA0);
                case 2:         // log scale
                    newVol = pot_log_scale(pinA0);
                    break;

                case 4:         // linear upside down
                    pinA0 = (MAX_ANALOG_VALUE - pinA0);
                case 1:         // linear
                    newVol = (pinA0 * MAX_VOLUME) / (MAX_ANALOG_VALUE);
                    break;
            }
            if (((globalConfig.actVolume > newVol) && ((globalConfig.actVolume - newVol) > 4)) ||
                ((newVol > globalConfig.actVolume) && ((newVol - globalConfig.actVolume) > 4))) {
                Serial.print(F("New volume "));
                Serial.println(newVol);
            }
            globalConfig.actVolume = newVol;
        }
        /* Feature 4:
         * update a display for output */
#if BUILD_GUI_LIB
        if (globalConfig.featureEn[FEATURE_DISPLAY]) {
            // update the display
# if 1
            if ((curRotate != globalConfig.featureEn[FEATURE_DISPLAY]) &&
                (0 == scr_need_up))
            {
                curRotate = globalConfig.featureEn[FEATURE_DISPLAY]; // newRotate;
                tft.setRotation(ADA_LIB_ROTATE(curRotate));
                Serial.print(F("rotate ")); Serial.println(curRotate, DEC); 
                dispFreq = desiredFreq;
                scr_need_up = 1;
            }
            else
#endif
            if (dispFreq != desiredFreq)
            {
                Serial.print(F("freq")); Serial.println(desiredFreq, DEC); 
                dispFreq = desiredFreq;
#if 1
                if (0 == scr_need_up)
                {
                int adjust_y = FIRST_LINE_SIZE * 8 * 2;
                if (PORTRAIT_ROTATE(curRotate)) 
                    adjust_y += FIRST_LINE_SIZE * 8;
            //  tft.fill(BACKGROUND_COLOR);
                tft.rect(0, adjust_y, 
                            tft.Adafruit_SPITFT::width(),
                            SECOND_LINE_SIZE * 8);
                tft.setCursor(0, adjust_y);
                myText(2);  // re-draw second line
                } else
#endif
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
                if (curRotate != globalConfig.featureEn[FEATURE_DISPLAY]) {
                    curRotate = globalConfig.featureEn[FEATURE_DISPLAY];
                    tft.setRotation(ADA_LIB_ROTATE(curRotate));
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
      tft.fillScreen(BACKGROUND_COLOR);
      tft.fill(BACKGROUND_COLOR);
      tft.setCursor(0, 0);
      break;
    case 1:
      tft.setTextSize(FIRST_LINE_SIZE);
      tft.setTextColor(FIRST_LINE_COLOR);
      tft.println(FIRST_LINE_TEXT);
      tft.println();
      break;
    case 2:
      tft.setTextSize(SECOND_LINE_SIZE);              
      tft.setTextColor(SECOND_LINE_COLOR);
      tft.print( LANDSCAPE_ROTATE(curRotate) ? SECND_LINE_LONG : SECND_LINE_SHORT);
      if (MODE_FM == cur_Mode) {
        UINT Mhz, Khz = (dispFreq / 10) % 10;
        Mhz = dispFreq / 100;
        tft.print(Mhz);
        tft.print('.');
        if ((100 <= Mhz))   // && (PORTRAIT_ROTATE(curRotate)))
            tft.print(Khz);
        else
            tft.println(Khz);
      } else 
        tft.println(dispFreq);
      break;
    case 3:
      tft.setTextSize(SPACE_LINE_SIZE);
      tft.println();
      tft.setTextColor(THIRD_LINE_COLOR);
      tft.setTextSize(THIRD_LINE_SIZE);  tft.print(THIRD_LINE_TEXT);
      break;
    case 4:
      if (PORTRAIT_ROTATE(curRotate))  tft.println();
      tft.setTextSize(FOURTH_LINE_SIZE);  tft.println(FOURTH_LINE_TEXT);
      // if (PORTRAIT_ROTATE(curRotate))  tft.println();
      tft.setTextSize(DEBUG_TEXT_SIZE);
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
  if LANDSCAPE_ROTATE(curRotate)
   return (line >= (12 -1));
 return (line >= (16 -1));
}
#endif

#endif  // #ifdef BUILD_APPLICATION - whole file
