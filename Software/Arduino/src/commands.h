/*
Software Controlled Radio - Command Definitions
*/

#ifndef COMMANDS_H
#define COMMANDS_H

#define triggerPin      13       // pin to charge the capacitor - connected to one end of the charging resistor
#define pulseInPin      10

typedef const char * processor_t(char * cmd);
typedef processor_t * processor_p;

typedef struct {
    char cmd[4];
    processor_p processor;
} command;

const char * read_Cap(char * cmd);
processor_t set_freq;
processor_t set_band;
processor_t set_volume;
processor_t get_freq;
processor_t enable_feature;
processor_t disable_feature;
processor_t save_cfg;

// extern command command_list[];
// Error codes (commands always return * strings)
// #define SUCCESS "0"
// #define INVALID_COMMAND "-1"
// #define INVALID_ARG "-2"

#endif