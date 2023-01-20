/* Load and Save configuration data in atomega328 EEPROM
*/

#include "select_build.h"
#include "arduino_radio.h"

#ifdef BUILD_APPLICATION

#if USE_EEPROM
#include <EEPROM.h>
#endif
#include "display.h"

/* Where in the EEPROM space do we start */
#define STARTING_LOCATION 0

CONFIG globalConfig;

static const CONFIG default_config {
    "VER-001",
    sizeof(CONFIG),
    0,             // first band
    (MAX_VOLUME * 2) / 3,
    DEFAULT_ROTATE,
    {
        0,
        0,
        0,
        0 // == USE_EEPROM
    },
    {  10070, 1030, 0 },
    {
        { MODE_FM, 0, 8400, 10800 },
        { MODE_AM, 0,  520,  1750 },
        { MODE_NOT_VALID, 0, 0, 0 }
    }
};

void save_config(void)
{
    write_config(0, sizeof(CONFIG));
}

void load_config(void)
{
#if USE_EEPROM
    char * cfg;
    UINT i;
    BOOL valid = true;

    Serial.print( "Config size " );
    Serial.println( sizeof(CONFIG) );

    // read everything we expect from the flash
    cfg = (char *) & globalConfig;
    for (i=0; i < sizeof(CONFIG); i++) {
        char ch = EEPROM.read( STARTING_LOCATION + i);
        * cfg = ch;
        cfg ++;
    }

# if 1
    // Is configuration valid?
    for (i=0; i < SIZE_OF_CONFIG_VERS; i++) {
        if (globalConfig.version[i] != default_config.version[i] ) {
            valid = false;
            Serial.println( "Config fails version." );
            break;
        }
    }
#  if 0
 /* if (0 > globalConfig.actBand) || */ 
    if (NUM_BANDS <= globalConfig.actBand) {
            valid = false;
            Serial.println( "Config fails band." );
    }
#  endif
    if (sizeof(CONFIG) != globalConfig.cfgSize) {
        Serial.print( "Config has changed from " );
        Serial.print( globalConfig.cfgSize );
        Serial.print( " to " );
        Serial.println( sizeof(CONFIG) );
        valid = false;
    }

    if (false == valid) {
        memcpy( & globalConfig, & default_config, sizeof(CONFIG));
        save_config();
    }
# else
   // memcpy( & globalConfig, & default_config, sizeof(CONFIG));
# endif
#else
    memcpy( & globalConfig, & default_config, sizeof(CONFIG));
#endif
}

void write_config(UCHAR offset, UCHAR size)
{
#if USE_EEPROM
    char * cfg, ch;
    UINT i;
    cfg = (char *) & globalConfig + offset;
    for (i=offset; i < (offset + size); i++ ) {
        ch = * cfg;
        EEPROM.write(STARTING_LOCATION + i, ch);
        cfg ++;
    }
#endif
}
#endif  // #ifdef BUILD_APPLICATION - whole file
