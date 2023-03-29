/* Load and Save configuration data in atomega328 EEPROM
*/

#include "select_build.h"
#include "arduino_radio.h"

#ifdef BUILD_APPLICATION

#if USE_EEPROM
#include <EEPROM.h>
#endif
#include "display.h"

#define NUM_LOG_STEPS   8
#define SIZE_LOG_STEP   ((MAX_ANALOG_VALUE + 1) / NUM_LOG_STEPS)

static const UCHAR log_offset[NUM_LOG_STEPS] =
    { 0, 32, 48, 56, 60, 62, 63, MAX_VOLUME };

UCHAR pot_log_scale(A2D_VAL volIn)
{
    int div, mod;
    UCHAR powTwo, baseOff;

    div = volIn / SIZE_LOG_STEP;
    mod = volIn % SIZE_LOG_STEP;

    powTwo =  2 + div;
    baseOff = log_offset[div];

    return (baseOff + (mod >> powTwo));
}  // potentiometer

FREQ_VAL roundToBandwidth(FREQ_VAL freqIn)
{
    BAND_CFG * bandCfg;
    FREQ_VAL result, minFre, spacing, diff;
    int curBand = globalConfig.actBand;

    bandCfg = & globalConfig.bands[curBand];
    result = freqIn;
    minFre = bandCfg->minFreq;
    if (MODE_FM == bandCfg->mode) {
        spacing = 200;      // commerical FM is 200 KHz spacing
        if ((0 < bandCfg->bw) && (NUM_BW_DEF_FM > bandCfg->bw))
            spacing = bandwidthFM[bandCfg->bw];
        result *= 10;
        minFre *= 10;
    } else {
        spacing = 1;        // assume 1 KHz spacing
        if ((0 < bandCfg->bw) && (NUM_BW_DEF_AM > bandCfg->bw))
            spacing = bandwidthAM[bandCfg->bw];
    }
    diff = result - minFre;
    diff = (diff + (spacing / 2)) / spacing;
    result = minFre + (diff * spacing);
    if (MODE_FM == bandCfg->mode) {
        result += spacing / 2;
        result = result / 10;
    }
    return result;
}

/* Where in the EEPROM space do we start */
#define STARTING_LOCATION 0

CONFIG globalConfig;

static const CONFIG default_config {
    "VER-001",
    sizeof(CONFIG),
    0,              // first band
    (MAX_VOLUME * 2) / 3,
    0,              // number of positions in the band switch must be calibrated 
    {               // featureEn[]
        0,
        0,
        0,
        0 // == USE_EEPROM
    },
    {  10070, 1030, 0 },    // actFreq[]
    {               // bands[]
        { MODE_FM, 0, 8400, 10800 },
        { MODE_AM, 0,  520,  1750 },
        { MODE_NOT_VALID, 0, 0, 0 }
    },
    { 85, 255, 426, 597, 768 }, // tunerCal[5]
    { 0, MAX_ANALOG_VALUE } // bndSwCal[]
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

    Serial.print( F("Config size ") );
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
            Serial.println( F("Config fails version.") );
            break;
        }
    }
#  if 0
 /* if (0 > globalConfig.actBand) || */ 
    if (NUM_BANDS <= globalConfig.actBand) {
            valid = false;
            Serial.println( F("Config fails band.") );
    }
#  endif
    if (sizeof(CONFIG) != globalConfig.cfgSize) {
        Serial.print( F("Config has changed from ") );
        Serial.print( globalConfig.cfgSize );
        Serial.print( F(" to ") );
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
