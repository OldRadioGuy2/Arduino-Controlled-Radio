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
    BAND_AM,
    BAND_FM,
    BAND_SSB,
    NUM_BANDS
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

typedef struct {
    char version[SIZE_OF_CONFIG_VERS];
    UINT cfgSize;
    UINT frequency[NUM_BANDS];
    CHAR band;
   UCHAR volume;
   UCHAR scrRotate;
    CHAR featureEn[NUM_FEATURES];
} CONFIG;

void load_config(void); // Load config from EEPROM using default if invalid
void save_config(void);     // Save the Config to EEPROM

extern const char * const bandStrings[NUM_BANDS];

extern CONFIG globalConfig;

extern SI4735 rx;

