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

const char * const bandStrings[NUM_BANDS] = {
     " AM",
     " FM",
     " SSB"
};

int my_atoi(char * str)
{
     char ch;
     int num = 0; int valid_chars = 0;
     do {
          ch = * str;
          if ((ch >= '0') && (ch <= '9'))
          {
               num = (num * 10) + (ch - '0');
               valid_chars ++;
          } else 
          if ((',' == ch) && (valid_chars))
               break;
          str ++;
     } while ('\0' != ch);
     return num;
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
    int freq = my_atoi(& cmd[2]);
    if ((1 <= dbg_verbose) || (0 != BLE_command)) {
          Serial.print(" Set Frequency ");
          Serial.println(freq);
     }
    if (0 != freq) {
        if (BAND_FM == globalConfig.band)
             freq *= 10;
        globalConfig.frequency[ (int)globalConfig.band] = freq;
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
    int band = my_atoi(& cmd[2]);
    if ((0 < band) && (NUM_BANDS >= band)) {
         if ((1 <= dbg_verbose) || (0 != BLE_command)) {
               Serial.print(" Set band");
               Serial.println(bandStrings[ band -1 ]);
          }
        globalConfig.band = band -1;
        return goodRet;
    } 
    Serial.print("Set band ignored.");
    return bad_Ret;
}

// Absolute volume in  the range of 0 - MAX_VOLUME
const char * set_volume(char * cmd)
{
    int volume = my_atoi(& cmd[2]);
         if ((1 <= dbg_verbose) || (0 != BLE_command)) {
          Serial.print(" Set volume ");
          Serial.println(volume);
      }
    if (MAX_VOLUME >= volume) {
        globalConfig.volume = volume;
        return goodRet;
    }
    return bad_Ret;
}

const char * get_freq(char * cmd)
{
     UINT currentFrequency;
     CHAR band = globalConfig.band;
 
#if BUILD_RADIO
     Serial.print(" The Si473X frequency is ");
     currentFrequency = rx.getFrequency();
#else
     currentFrequency = globalConfig.frequency[ (int)band ];
#endif
     if (BAND_FM == band) {
          UINT kiloHz = currentFrequency % 100;
          currentFrequency = currentFrequency / 100;
          kiloHz = kiloHz / 10;
          Serial.print(currentFrequency);
          Serial.print(".");
          Serial.print(kiloHz);
     } else
          Serial.print(currentFrequency);
     Serial.println(bandStrings[ (int)band ]);
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
          int band = globalConfig.band;
#if 1
          Serial.print( " Band ");
          Serial.println( band );
#else
          Serial.println(bandStrings[ (int)band ]);
#endif
     sprintf_1(band);
     return val_Ret;
}

const char * get_volume(char * cmd)
{
     Serial.print( " Volume ");
     Serial.println( globalConfig.volume );
     sprintf_1( globalConfig.volume);
     return val_Ret;
}

const char * create_band(char * cmd)
{
          Serial.println( " Create Band not imp." );
          return bad_Ret;
}

const char * delete_band(char * cmd)
{
          Serial.println( " Delete Band not imp." );
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
    int featEn = my_atoi(& cmd[2]);
    if ((0 == featEn) || (1 == featEn)) {
          Serial.print(" Enable volume ");
          Serial.println(featEn);
          globalConfig.featureEn[FEATURE_VOLUME] = featEn;
     }
    return goodRet;
}

const char * tuning_feature(char * cmd)
{
    int featEn = my_atoi(& cmd[2]);
    if ((0 == featEn) || (1 == featEn)) {
          Serial.print(" Enable tuning ");
          Serial.println(featEn);
          globalConfig.featureEn[FEATURE_FREQ_CAP] = featEn;
     }
    return goodRet;
}

const char * band_sw_feature(char * cmd)
{
    int featEn = my_atoi(& cmd[2]);
    if ((0 == featEn) || (1 == featEn)) {
          Serial.print(" Enable Band switch ");
          Serial.println(featEn);
          globalConfig.featureEn[FEATURE_BAND_SW] = featEn;
     }
    return goodRet;
}

const char * display_feature(char * cmd)
{
    int featEn = my_atoi(& cmd[2]);
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
    int rote = my_atoi(& cmd[2]);
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
