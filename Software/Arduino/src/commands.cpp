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
               mode = MODE_SSB;
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

CAP_RD_VAL measure_Cap_timing(int verbose)
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
   if (verbose) {
      Serial.print( res);       // print the value to serial port
      Serial.print(F(" counts, "));      // print units and carriage return
      Serial.print( (end - start) >> 2);       // print the value to serial port
      Serial.println(F(" u-sec."));      // print units and carriage return
   }
    return (CAP_RD_VAL)res;
}

// Absolute frequecy, FM is in 10's of killihertz
const char * set_freq(char * cmd)
{
    FREQ_VAL freqIn, freqOut;
    int cmdStart = 2;
    int band = globalConfig.actBand;
    int mode = globalConfig.bands[band].mode;
    freqIn = my_atoi(cmd, & cmdStart);

    if (0 != freqIn) {
        if (MODE_FM == mode)
             freqIn *= 10;
        freqOut = roundToBandwidth(freqIn);
          if ((1 <= dbg_verbose) || (0 != BLE_command)) {
                    Serial.print(F(" Set Frequency "));
                    Serial.println(freqOut);
               }
        globalConfig.actFreq[ band ] = freqOut;
        write_config( ((char *) & globalConfig.actFreq[ band ]) - globalConfig.version,
                                  sizeof(globalConfig.actFreq[0]));
        if ((MODE_NOT_VALID != mode) && (false == mode_is_valid))
          forceBand = 1;
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
    if ((BAND_ONES_OFFSET <= band) &&
        ((NUM_BANDS + BAND_ONES_OFFSET) > band)) {
# if BAND_ONES_OFFSET
         band --;
# endif
         globalConfig.actBand = band;
         mode = globalConfig.bands[band].mode;

         if ((1 <= dbg_verbose) || (0 != BLE_command)) {
               Serial.print(F(" Set band "));
               Serial.print( band + BAND_ONES_OFFSET);
               Serial.println( modeStrings[ mode ]);
          }
        write_config( ((char *) & globalConfig.actBand) - globalConfig.version, sizeof(globalConfig.actBand));
        return goodRet;
    } 
    Serial.print(F("Set band ignored."));
    return bad_Ret;
}

// Absolute volume in  the range of 0 - MAX_VOLUME
const char * set_volume(char * cmd)
{
    int cmdStart = 2;
    int volume = my_atoi(cmd, & cmdStart);

    if ((1 <= dbg_verbose) || (0 != BLE_command)) {
          Serial.print(F(" Set volume "));
          Serial.println(volume);
     }
    if (MAX_VOLUME >= volume) {
        globalConfig.actVolume = volume;
        write_config( ((char *) & globalConfig.actVolume) - globalConfig.version, sizeof(globalConfig.actVolume));
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
     Serial.print(F(" The Si473X frequency is "));
     currentFrequency = rx.getFrequency();
#else
     currentFrequency = globalConfig.actFreq[ band ];
#endif
     sprintf_1(currentFrequency);
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

     return val_Ret;
}

const char * get_sig_lvl(char * cmd)
{
     uint8_t sigStr = rx.getReceivedSignalStrengthIndicator();
     uint8_t sigSNR = rx.getStatusSNR();
     Serial.print( F(" Sig strength ") );
     Serial.println( sigStr );

     Serial.print( F(" SNR ") );
     Serial.println( sigSNR );

     Serial.print( F("Signal: ") );
     Serial.print(rx.getCurrentRSSI());
     Serial.println(F("dBuV"));

     sprintf_2(sigStr, sigSNR);
     return val_Ret;
}

const char * get_band(char * cmd)
{
     int band = globalConfig.actBand;
     int mode = globalConfig.bands[band].mode;

# if BAND_ONES_OFFSET
     band ++;
# endif
     Serial.print( F(" Band "));
     Serial.println( band );
     Serial.println( modeStrings[ mode ]);
     sprintf_1(band);
     return val_Ret;
}

const char * get_volume(char * cmd)
{
     Serial.print( F(" Volume "));
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
#if 0
    Serial.print( F(" Create Band ") );
    Serial.print( band );
    Serial.print( modeStrings[ mode ]);
    Serial.print( F(" min ") );
    Serial.print( fMin );
    Serial.print( F(" max ") );
    Serial.print( fMax );
    Serial.print( F(" bw ") );
    Serial.println( obw );
#endif
    if ((BAND_ONES_OFFSET <= band) &&
        ((NUM_BANDS + BAND_ONES_OFFSET) > band)) { 
        BAND_CFG * bandCfg;
# if BAND_ONES_OFFSET
         band --;
# endif
        bandCfg = & globalConfig.bands[band];
        bandCfg->mode = mode;
        bandCfg->bw = obw;
        bandCfg->minFreq = fMin;
        bandCfg->maxFreq = fMax;
        if (band == globalConfig.actBand)
            forceBand = 1;
        write_config( (char *) bandCfg - globalConfig.version, sizeof(BAND_CFG));
        return goodRet;
     }
     return bad_Ret;
}

const char * delete_band(char * cmd)
{
    int cmdStart = 2;
    int band = my_atoi(cmd, & cmdStart);
    Serial.print( F(" Delete Band ") );
    Serial.println( band );
    if ((BAND_ONES_OFFSET <= band) &&
        ((NUM_BANDS + BAND_ONES_OFFSET) > band)) {
        BAND_CFG * bandCfg;
# if BAND_ONES_OFFSET
         band --;
# endif
        bandCfg = & globalConfig.bands[band];
        bandCfg->mode = MODE_NOT_VALID;
        if (band == globalConfig.actBand)
            forceBand = 1;
        write_config( (char *) bandCfg - globalConfig.version, sizeof(BAND_CFG));
        return goodRet;
    }
    return bad_Ret;
}

/*  */
const char * calibrate_tuner(char * cmd)
{
    int cmdStart = 2;
    UCHAR tuneIndex = my_atoi(cmd, & cmdStart);
    if (NUM_TUNE_CONFIG > tuneIndex) {
          CAP_RD_VAL tuner = measure_Cap_timing( true );
          globalConfig.tunerCal[tuneIndex] = tuner;

    if ((NUM_TUNE_CONFIG -1) == tuneIndex)
          write_config( ((char *) & globalConfig.tunerCal[0]) - globalConfig.version,
                              sizeof(globalConfig.tunerCal));
     sprintf_1( tuner);
     return val_Ret;
    }
     return bad_Ret;
}

/* save off the intermediate values */
UCHAR last_band_index = 0;        // CBn, 1- based
A2D_VAL last_band_value = MIN_ANALOG_VALUE;

const char * calibrate_band(char * cmd)
{
    int cmdStart = 2;
    UCHAR bIndex = my_atoi(cmd, & cmdStart);
    if (0 == bIndex) {
          Serial.print( F(" Band switch with ") );
          Serial.print( last_band_index );
          Serial.println( F(" bands enabled") );
          globalConfig.numBandCfg = last_band_index;

          write_config( ((char *) & globalConfig.numBandCfg) - globalConfig.version,
                              sizeof(globalConfig.numBandCfg));
          write_config( ((char *) & globalConfig.bndSwCal[0]) - globalConfig.version,
                              sizeof(globalConfig.bndSwCal));
          last_band_index = 0;        // CBn, 1- based
          last_band_value = MIN_ANALOG_VALUE;
#if 1
     sprintf_1( globalConfig.numBandCfg);
     return val_Ret;
#else
       return goodRet;
#endif
    }
    if (NUM_BANDS >= bIndex) {
          A2D_VAL bandPin = analogRead(analogBandSwitch);

          Serial.print( F(" Cal Band ") );
          Serial.print( bIndex );
          Serial.print( F(" read ") );
          Serial.println( bandPin );

          if ((last_band_index + 1) == bIndex) {
               // for (1 == bIndex) case, we have insured 
               // both last_band_index = 0 and last_band_value = 0
               globalConfig.bndSwCal[last_band_index] = (bandPin + last_band_value) / 2;
          } else {
              Serial.println( F("out of order.") );
          }
          last_band_index = bIndex;
          last_band_value = bandPin;
     sprintf_1( bandPin);
     return val_Ret;
    }
    return bad_Ret;
}

const char * volume_feature(char * cmd)
{
    int cmdStart = 2;
    int featEn = my_atoi(cmd, & cmdStart);
    if ((0 <= featEn) && (6 >= featEn)) {
          Serial.print(F(" Enable volume "));
          Serial.println(featEn);
          globalConfig.featureEn[FEATURE_VOLUME] = featEn;
          write_config( ((char *) & globalConfig.featureEn[FEATURE_VOLUME]) - globalConfig.version,
                              sizeof(globalConfig.featureEn[FEATURE_VOLUME]));
         return goodRet;
     }
    return bad_Ret;
}

const char * tuning_feature(char * cmd)
{
    int cmdStart = 2;
    int featEn = my_atoi(cmd, & cmdStart);
    if ((0 == featEn) || (1 == featEn)) {
          Serial.print(F(" Enable tuning "));
          Serial.println(featEn);
          globalConfig.featureEn[FEATURE_FREQ_CAP] = featEn;
          write_config( ((char *) & globalConfig.featureEn[FEATURE_FREQ_CAP]) - globalConfig.version,
                              sizeof(globalConfig.featureEn[FEATURE_FREQ_CAP]));
         return goodRet;
     }
    return bad_Ret;
}

const char * band_sw_feature(char * cmd)
{
    int cmdStart = 2;
    int featEn = my_atoi(cmd, & cmdStart);
    if ((0 <= featEn) && (NUM_BAND_CONFIG >= featEn)) {
          Serial.print(F(" Enable Band sw "));
          Serial.println(featEn);
          globalConfig.featureEn[FEATURE_BAND_SW] = featEn;
          write_config( ((char *) & globalConfig.featureEn[FEATURE_BAND_SW]) - globalConfig.version,
                              sizeof(globalConfig.featureEn[FEATURE_BAND_SW]));
         return goodRet;
     }
    return bad_Ret;
}

const char * display_feature(char * cmd)
{
    int cmdStart = 2;
    int featEn = my_atoi(cmd, & cmdStart);
    if ((0 <= featEn) && (4 >= featEn)) {
          Serial.print(F(" En/rotate display "));
          Serial.println(featEn);
          globalConfig.featureEn[FEATURE_DISPLAY] = featEn;
          write_config( ((char *) & globalConfig.featureEn[FEATURE_DISPLAY]) - globalConfig.version,
                              sizeof(globalConfig.featureEn[FEATURE_DISPLAY]));
         return goodRet;
     }
    return bad_Ret;
}

const char * save_cfg(char * cmd)
{
    Serial.println( F(" Save config."));
    save_config();
    return goodRet;
}

const char * read_Cap(char * cmd)
{
    unsigned int res = measure_Cap_timing( true );
#if 1
     sprintf_1( res);
     return val_Ret;
#else
    return goodRet;
#endif
}
#endif  // #ifdef BUILD_APPLICATION - whole file
