/* Command Processors
*/
#include <Arduino.h>
#include <SI4735.h>

#include "arduino_radio.h"
#include "commands.h"

const char dummyRet[] = " 0";

const char * process_sf(char * cmd)
{
    return dummyRet;
}
const char * process_sb(char * cmd)
{
    return dummyRet;
}
const char * process_gf(char * cmd)
{
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

