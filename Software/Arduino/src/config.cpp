/* Load and Save configuration data in atomega328 EEPROM
*/

#include <Arduino.h>
#include <EEPROM.h>
#include "arduino_radio.h"

#define STARTING_LOCATION 0

CONFIG Config;

CONFIG default_config {
    CONFIG_VERSION,
    AM,
    1030,
    30,
    false,
    false,
    false
};

CONFIG *get_config() {
    return &Config;
}

CONFIG * load_config(){
    // Is configuration valid?
    char c;
    for (int i=0; i < sizeof(CONFIG_VERSION); i++) {
        if ( EEPROM.read( STARTING_LOCATION+ offsetof(CONFIG , version)+i) != default_config.version[i] ){
            memcpy( &Config, &default_config, sizeof(Config));
            save_config();
        }
        else {
            for (int i=0; i < sizeof(CONFIG); i++ ) {
                * (UCHAR *) (&Config + i) = EEPROM.read(STARTING_LOCATION+i);
            }

        }
    }
    return &Config;
}

void save_config() {
    for (int i=0; i < sizeof(CONFIG); i++ ) {
        EEPROM.write(STARTING_LOCATION+i, * (UCHAR *) (&Config + i) );
    }
}