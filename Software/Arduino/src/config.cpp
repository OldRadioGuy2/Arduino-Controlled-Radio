/* Load and Save configuration data in atomega328 EEPROM
*/

#include "select_build.h"
#include "arduino_radio.h"

#ifdef BUILD_APPLICATION

#if USE_EEPROM
#include <EEPROM.h>
#endif

/* Where in the EEPROM space do we start */
#define STARTING_LOCATION 0

CONFIG globalConfig;

static const CONFIG default_config {
    "VER-001",
    sizeof(CONFIG),
    { 1030, 9950, 1030 },
    BAND_FM,
    MAX_VOLUME / 3,
    { 0, 0, 0, 0 }
};

void load_config(void)
{
#if USE_EEPROM
    char * cfg, ch;
    UINT i;
    BOOL valid = true;
    // read everything we expect from the flash
    cfg = (char *) & globalConfig;
    for (i=0; i < sizeof(CONFIG); i++) {
        ch = EEPROM.read( STARTING_LOCATION + i);
        * cfg = ch;
        cfg ++;
    }

    // Is configuration valid?
    for (i=0; i < SIZE_OF_CONFIG_VERS; i++) {
        if (globalConfig.version[i] != default_config.version[i] ) {
            valid = false;
            Serial.println( "Config fails version." );
            break;
        }
    }
    if ((globalConfig.band < BAND_AM) ||
        (globalConfig.band >= NUM_BANDS)) {
            valid = false;
            Serial.println( "Config fails band." );
        }
    if (false == valid) {
        memcpy( & globalConfig, & default_config, sizeof(CONFIG));
        save_config();
    } else
    if (sizeof(CONFIG) > globalConfig.cfgSize) {
        UINT first_feature_off = offsetof(CONFIG , featureEn[0]);
        Serial.print( "Config has grown from " );
        Serial.print( globalConfig.cfgSize );
        Serial.print( " to " );
        Serial.println( sizeof(CONFIG) );
        if (globalConfig.cfgSize > (first_feature_off + (FEATURE_DISPLAY * sizeof(CHAR)))) {
            int num_features_read = (globalConfig.cfgSize - first_feature_off) / sizeof(CHAR);
            do {
                globalConfig.featureEn[num_features_read] = default_config.featureEn[num_features_read];
                num_features_read ++;
            } while (NUM_FEATURES > num_features_read);
        }
    }
#endif
}

void save_config(void)
{
#if USE_EEPROM
    char * cfg, ch;
    UINT i;
    cfg = (char *) & globalConfig;
    for (i=0; i < sizeof(CONFIG); i++ ) {
        ch = * cfg;
        EEPROM.write(STARTING_LOCATION + i, ch);
        cfg ++;
    }
#endif
}
#endif  // #ifdef BUILD_APPLICATION - whole file
