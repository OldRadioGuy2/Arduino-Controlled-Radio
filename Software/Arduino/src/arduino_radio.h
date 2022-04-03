/* Global constants and typedefs
*/

#define INT int
#define UINT unsigned int
#define CHAR char
#define UCHAR unsigned char
#define BOOL bool

#define AM 0
#define FM 1
#define SSB 2

// Configuration memory
#define CONFIG_VERSION "VER001"

typedef struct {
    char version[sizeof(CONFIG_VERSION)];
    UINT band;
    UINT frequency;
    UINT volume;
    BOOL use_frequency_cap;
    BOOL use_volume_ctrl;
    BOOL use_band_switch; 
} CONFIG;

CONFIG * load_config(); // Load config from EEPROM using default if invalid
CONFIG * get_config();  // Return the Config address
void save_config();     // Save the Config to EEPROM

// Error codes (commands always return *strings)
#define SUCCESS "0"
#define INVALID_COMMAND "-1"
#define INVALID_ARG "-2"
