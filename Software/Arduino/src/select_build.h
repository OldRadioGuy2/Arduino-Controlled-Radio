/* Select whether to build the application or the 4735 test program.
*/

#define BUILD_APPLICATION
// #define BUILD_TEST_PROGRAM

#define NANO_ATMEGA_BOARD  1
#define NANO_BLE_BOARD     2

#define PLATFORM    NANO_ATMEGA_BOARD

#ifdef BUILD_APPLICATION
# define BUILD_GUI_LIB  0
#endif

#ifdef BUILD_TEST_PROGRAM
# define BUILD_GUI_LIB  0
#endif

#if PLATFORM  == NANO_ATMEGA_BOARD
# define USE_EEPROM  1
#else
# define USE_EEPROM  0
#endif
