/* Command Processors
*/

#include "select_build.h"
#include "arduino_radio.h"
#include "commands.h"

#ifdef BUILD_APPLICATION

const char goodRet[] = "0";
const char val_Ret[] = "0,";
const char bad_Ret[] = "1";

char dbg_verbose = 1;

const char * const modeStrings[NUM_MODES] = {
     " not valid",
     " AM",
     " FM",
     " SSB"
};

int my_atoi(char * str, int * inp)
{
     char ch, valid_chars = 0;
     int index, num = 0;
     index = * inp;
     do {
          ch = str[index];
          if ((ch >= '0') && (ch <= '9'))
          {
               num = (num * 10) + (ch - '0');
               valid_chars ++;
          } else 
          if ((',' == ch) && (valid_chars))
               break;
          index ++;
     } while ('\0' != ch);
     * inp = index;
     return num;
}
int my_mode(char * str, int * inp)
{
     char ch, valid_chars = 0;
     int index, mode = MODE_NOT_VALID;
     index = * inp;
     do {
          ch = str[index];
          if ((ch == 'a') || (ch == 'A'))
          {
               mode = MODE_AM;
               valid_chars ++;
          } else 
          if ((ch == 'f') || (ch == 'F'))
          {
               mode = MODE_FM;
               valid_chars ++;
          } else 
          if ((ch == 's') || (ch == 'S'))
          {
               mode = MODE_FM;
               valid_chars ++;
          } else 
          if ((ch == 'm') || (ch == 'M') ||
              (ch == 'b') || (ch == 'B'))
          {
               valid_chars ++;
          } else 
          if ((',' == ch) && (valid_chars))
               break;
          index ++;
     } while ('\0' != ch);
     * inp = index;
     return mode;
}

int my_sprintf(char * buf, int value)
{
     int modVal, divisor = 10000;
     int out_ptr = 0;

     modVal = value;
     do {
          int digit = modVal / divisor;
          if (digit || out_ptr || (1 == divisor)) {
               buf[out_ptr] = (char)(digit + '0');
               modVal -= (digit * divisor);
               out_ptr ++;
          }
          divisor = divisor / 10;
     } while (divisor);
     buf[out_ptr] = '\0';
     return out_ptr;
}

void sprintf_1( int value)
{
     my_sprintf(fmt_rsp_buffer, value);
}

void sprintf_2(int val1, int val2)
{
     int fst = my_sprintf(fmt_rsp_buffer, val1);
     fmt_rsp_buffer[fst] = ',';
     my_sprintf(& fmt_rsp_buffer[fst + 1], val2);
}

unsigned int measure_Cap_timing(void)
{
  unsigned long start, end, res;

     digitalWrite(triggerPin, LOW);  // set chargePin HIGH and capacitor charging
     delayMicroseconds(5);
     start = micros();
     digitalWrite(triggerPin, HIGH);  // set chargePin HIGH and capacitor charging
#if 0
     while (0 != digitalRead(pulseInPin)) ;
#elif 0
     // res = pulseIn(pulseInPin, HIGH, 3000000UL);
     res = pulseInLong(pulseInPin, HIGH, 3000000UL);
#else
     res = 0;
     while ((0 != digitalRead(pulseInPin)) &&
            (res < 3000000))
       res ++;
#endif
     end = micros();
 //  interrupts();

   /* dicharge the capacitor  */
      Serial.print( res);       // print the value to serial port
      Serial.print(" counts, ");      // print units and carriage return
      Serial.print( (end - start) >> 2);       // print the value to serial port
      Serial.println(" u-sec.");      // print units and carriage return

    return (unsigned int)res;
}

// Absolute frequecy, FM is in 10's of killihertz
const char * set_freq(char * cmd)
{
    int cmdStart = 2;
    int band = globalConfig.actBand;
    int mode = globalConfig.bands[band].mode;
    int freq = my_atoi(cmd, & cmdStart);

    if ((1 <= dbg_verbose) || (0 != BLE_command)) {
          Serial.print(" Set Frequency ");
          Serial.println(freq);
     }
    if (0 != freq) {
        if (MODE_FM == mode)
             freq *= 10;
        globalConfig.actFreq[ band ] = freq;
     return goodRet;
    }
    return bad_Ret;
}

// Band is 1-based :
//  BAND_AM = 1,
//  BAND_FM = 2,
//  BAND_SSB = 3 
const char * set_band(char * cmd)
{
    int cmdStart = 2;
    int band = my_atoi(cmd, & cmdStart);
    int mode;
    if ((0 < band) && (NUM_BANDS >= band)) {
         band --;
         globalConfig.actBand = band;
         mode = globalConfig.bands[band].mode;

         if ((1 <= dbg_verbose) || (0 != BLE_command)) {
               Serial.print(" Set band");
               Serial.print( band );
               Serial.println( modeStrings[ mode ]);
          }
        return goodRet;
    } 
    Serial.print("Set band ignored.");
    return bad_Ret;
}

// Absolute volume in  the range of 0 - MAX_VOLUME
const char * set_volume(char * cmd)
{
    int cmdStart = 2;
    int volume = my_atoi(cmd, & cmdStart);

    if ((1 <= dbg_verbose) || (0 != BLE_command)) {
          Serial.print(" Set volume ");
          Serial.println(volume);
     }
    if (MAX_VOLUME >= volume) {
        globalConfig.actVolume = volume;
        return goodRet;
    }
    return bad_Ret;
}

const char * get_freq(char * cmd)
{
     int band = globalConfig.actBand;
     int mode = globalConfig.bands[band].mode;
     UINT currentFrequency;

#if BUILD_RADIO
     Serial.print(" The Si473X frequency is ");
     currentFrequency = rx.getFrequency();
#else
     currentFrequency = globalConfig.frequency[ band ];
#endif
     if (MODE_FM == mode) {
          UINT kiloHz = currentFrequency % 100;
          currentFrequency = currentFrequency / 100;
          kiloHz = kiloHz / 10;
          Serial.print(currentFrequency);
          Serial.print(".");
          Serial.print(kiloHz);
     } else
          Serial.print(currentFrequency);
     Serial.println( modeStrings[ mode ]);
     sprintf_1(currentFrequency);

     return val_Ret;
}

const char * get_sig_lvl(char * cmd)
{
          Serial.println( " Sig Level not imp." );
          return bad_Ret;
}

const char * get_band(char * cmd)
{
     int band = globalConfig.actBand;
     int mode = globalConfig.bands[band].mode;

     Serial.print( " Band ");
     Serial.println( band );
     Serial.println( modeStrings[ mode ]);
     sprintf_1(band);
     return val_Ret;
}

const char * get_volume(char * cmd)
{
     Serial.print( " Volume ");
     Serial.println( globalConfig.actVolume );
     sprintf_1( globalConfig.actVolume);
     return val_Ret;
}

const char * create_band(char * cmd)
{
    int cmdStart = 2;
    int band = my_atoi(cmd, & cmdStart);
    int mode = my_mode(cmd, & cmdStart);
    int fMin = my_atoi(cmd, & cmdStart);
    int fMax = my_atoi(cmd, & cmdStart);
    int obw  = my_atoi(cmd, & cmdStart);

    Serial.print( " Create Band " );
    Serial.print( band );
    Serial.print( modeStrings[ mode ]);
    Serial.print( " min " );
    Serial.print( fMin );
    Serial.print( " max " );
    Serial.print( fMax );
    Serial.print( " bw " );
    Serial.println( obw );
    if ((0 <= band) && (NUM_BANDS > band)) {
        BAND_CFG * bandCfg = & globalConfig.bands[band];
        bandCfg->mode = mode;
        bandCfg->bw = obw;
        bandCfg->minFreq = fMin;
        bandCfg->maxFreq = fMax;
        if (band == globalConfig.actBand)
            forceBand = 1;
        return goodRet;
     }
     return bad_Ret;
}

const char * delete_band(char * cmd)
{
    int cmdStart = 2;
    int band = my_atoi(cmd, & cmdStart);
    Serial.print( " Delete Band " );
    Serial.println( band );
    if ((0 <= band) && (NUM_BANDS > band)) {
        BAND_CFG * bandCfg = & globalConfig.bands[band];
        bandCfg->mode = MODE_NOT_VALID;
        if (band == globalConfig.actBand)
            forceBand = 1;
        return goodRet;
    }
    return bad_Ret;
}

const char * calibrate_tuner(char * cmd)
{
          Serial.println( " Cal Tunernot imp." );
          return bad_Ret;
}

const char * calibrate_band(char * cmd)
{
          Serial.println( " Cal Band not imp." );
          return bad_Ret;
}

const char * volume_feature(char * cmd)
{
    int cmdStart = 2;
    int featEn = my_atoi(cmd, & cmdStart);
    if ((0 == featEn) || (1 == featEn)) {
          Serial.print(" Enable volume ");
          Serial.println(featEn);
          globalConfig.featureEn[FEATURE_VOLUME] = featEn;
     }
    return goodRet;
}

const char * tuning_feature(char * cmd)
{
    int cmdStart = 2;
    int featEn = my_atoi(cmd, & cmdStart);
    if ((0 == featEn) || (1 == featEn)) {
          Serial.print(" Enable tuning ");
          Serial.println(featEn);
          globalConfig.featureEn[FEATURE_FREQ_CAP] = featEn;
     }
    return goodRet;
}

const char * band_sw_feature(char * cmd)
{
    int cmdStart = 2;
    int featEn = my_atoi(cmd, & cmdStart);
    if ((0 == featEn) || (1 == featEn)) {
          Serial.print(" Enable Band switch ");
          Serial.println(featEn);
          globalConfig.featureEn[FEATURE_BAND_SW] = featEn;
     }
    return goodRet;
}

const char * display_feature(char * cmd)
{
    int cmdStart = 2;
    int featEn = my_atoi(cmd, & cmdStart);
    if ((0 == featEn) || (1 == featEn)) {
          Serial.print(" Enable display ");
          Serial.println(featEn);
          globalConfig.featureEn[FEATURE_DISPLAY] = featEn;
     }
    return goodRet;
}

const char * save_cfg(char * cmd)
{
    Serial.println( " Save config.");
    save_config();
    return goodRet;
}

const char * screen_rotate(char * cmd)
{
    int cmdStart = 2;
    int rote = my_atoi(cmd, & cmdStart);
    Serial.print(" Rotate ");
    Serial.println(rote);
    if ((0 < rote) && (4 >= rote)) {
        globalConfig.scrRotate = rote -1;
    }
    return goodRet;
}

const char * read_Cap(char * cmd)
{
    // unsigned int res = 
    measure_Cap_timing();

    return goodRet;
}
#endif  // #ifdef BUILD_APPLICATION - whole file
