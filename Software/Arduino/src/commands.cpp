/* Command Processors
*/

#include "select_build.h"
#include "arduino_radio.h"
#include "commands.h"

#ifdef BUILD_APPLICATION

const char dummyRet[] = " 0";

const char * const bandStrings[NUM_BANDS] = {
     " AM",
     " FM",
     " SSB"
};

int my_atoi(char * str)
{
     char ch;
     int num = 0;
     do {
          ch = * str;
          if ((ch >= '0') && (ch <= '9'))
          {
               num = (num * 10) + (ch - '0');
          }
          str ++;
     } while ('\0' != ch);
     return num;
}

const char * set_freq(char * cmd)
{
    int freq = my_atoi(& cmd[2]);
    Serial.print(" Set Frequency ");
    Serial.println(freq);
    if (0 != freq)
        globalConfig.frequency[ (int)globalConfig.band] = freq;
    return dummyRet;
}

const char * set_band(char * cmd)
{
    int band = my_atoi(& cmd[2]);
    Serial.print(" Set band");
    if ((0 < band) && (NUM_BANDS >= band)) {
        Serial.println(bandStrings[ band -1 ]);
        globalConfig.band = band -1;
    } else
         Serial.print(" ignored.");
    return dummyRet;
}

const char * set_volume(char * cmd)
{
    int volume = my_atoi(& cmd[2]);
    Serial.print(" Set volume ");
    Serial.println(volume);
    if (MAX_VOLUME >= volume)
        globalConfig.volume = volume;
    return dummyRet;
}

const char * enable_feature(char * cmd)
{
    int featId = my_atoi(& cmd[2]);
    Serial.print(" Enable feature ");
    Serial.println(featId);
    if (NUM_FEATURES >= featId)
        globalConfig.featureEn[featId] = 1;
    return dummyRet;
}
const char * disable_feature(char * cmd)
{
    int featId = my_atoi(& cmd[2]);
    Serial.print(" Disable feature ");
    Serial.println(featId);
    if (NUM_FEATURES >= featId)
        globalConfig.featureEn[featId] = 0;
    return dummyRet;
}

const char * save_cfg(char * cmd)
{
    Serial.println( " Save config.");
     save_config();
     return dummyRet;
}

const char * get_freq(char * cmd)
{
     UINT currentFrequency;
     CHAR band = globalConfig.band;
 
     Serial.print(" The Si473X frequency is ");
     currentFrequency = rx.getFrequency();
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

     return dummyRet;
}

const char * read_Cap(char * cmd)
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

    return dummyRet;
}
#endif  // #ifdef BUILD_APPLICATION - whole file
