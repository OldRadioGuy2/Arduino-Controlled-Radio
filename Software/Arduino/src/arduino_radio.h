/* Global constants and typedefs
*/

#include <Arduino.h>
#include <SI4735.h>

typedef int INT;
typedef unsigned int UINT;
typedef char CHAR;
typedef unsigned char UCHAR;
typedef char BOOL;

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

#define NUM_BANDS 4

typedef struct {
    UCHAR mode;
    UCHAR bw;
    UINT  minFreq;
    UINT  maxFreq;
} BAND_CFG;

typedef struct {
    char version[SIZE_OF_CONFIG_VERS];
    UINT cfgSize;
    UINT actFreq[NUM_BANDS];
    CHAR actBand;
   UCHAR actVolume;
   UCHAR scrRotate;
    CHAR featureEn[NUM_FEATURES];
    BAND_CFG bands[NUM_BANDS];
} CONFIG;

void load_config(void); // Load config from EEPROM using default if invalid
void write_config(UCHAR offset, UCHAR size);    // Save some of the Config to EEPROM
void save_config(void);     // Save the entire Config to EEPROM

extern const char * const modeStrings[NUM_MODES];

extern CONFIG globalConfig;

extern SI4735 rx;

extern CHAR forceBand;
extern CHAR BLE_command;

