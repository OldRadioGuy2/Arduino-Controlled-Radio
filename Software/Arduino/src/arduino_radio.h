/* Global constants and typedefs
*/

#include <Arduino.h>
#include <SI4735.h>

/* run-of-the-mill type definitions */
typedef int INT;
typedef unsigned int UINT;
typedef char CHAR;
typedef unsigned char UCHAR;
typedef char BOOL;

typedef unsigned int FREQ_VAL;
/* our interface type definitions,
 * 10 bit A to D, tuning cap is a long */
typedef unsigned int A2D_VAL;
typedef unsigned int CAP_RD_VAL;
#define MAX_ANALOG_VALUE    (1 << 10)

/* radio library accepts volume in 0-63*/
#define MAX_VOLUME  63

enum band_selections {
    MODE_NOT_VALID,
    MODE_AM,
    MODE_FM,
    MODE_SSB,
    NUM_MODES
};

enum sel_features {
    FEATURE_FREQ_CAP,
    FEATURE_VOLUME,
    FEATURE_BAND_SW,
    FEATURE_DISPLAY,
    NUM_FEATURES
};

// Configuration memory
#define SIZE_OF_CONFIG_VERS 8

/* How many slots in the EEProm storage for [AM/FM min/max] bands */
#define NUM_BANDS             5
/* How many slots in the EEProm storage for analog band switch */
#define NUM_BAND_CONFIG    NUM_BANDS
/* How many slots in the EEProm storage for analog tuning */
#define NUM_TUNE_CONFIG       2

/* accept and print Band as 1-based */
#define BAND_ONES_OFFSET 1

typedef struct {
    UCHAR mode;
    UCHAR bw;
    FREQ_VAL  minFreq;
    FREQ_VAL  maxFreq;
} BAND_CFG;

typedef struct {
    char  version[SIZE_OF_CONFIG_VERS];
    UCHAR cfgSize;      // other way to know the struct has changed
    UCHAR actBand;      // which band is active ? 0-based
    UCHAR actVolume;    // 0 - 63
    UCHAR numBandCfg;   // number of bands for FEATURE_BAND_SW

    /* is volume knob supported, tuner cap, band switch, display enable ? */
    CHAR  featureEn[NUM_FEATURES];

    /* last frequency set for each band */
    FREQ_VAL actFreq[NUM_BANDS];

    /* slots for [AM/FM min/max] bands */
    BAND_CFG bands[NUM_BANDS];

    /* save calibration values for the band switch - resistor ladder */
    A2D_VAL  bndSwCal[NUM_BAND_CONFIG];

    /* save calibration values for the tuner cap */
    CAP_RD_VAL tunerCal[NUM_TUNE_CONFIG];
} CONFIG;

void load_config(void); // Load config from EEPROM using default if invalid
void write_config(UCHAR offset, UCHAR size);    // Save some of the Config to EEPROM
void save_config(void);     // Save the entire Config to EEPROM
CAP_RD_VAL measure_Cap_timing(int verbose);

extern const char * const modeStrings[NUM_MODES];

extern CONFIG globalConfig;

extern SI4735 rx;

extern CHAR forceBand;
extern CHAR BLE_command;
extern BOOL mode_is_valid;
