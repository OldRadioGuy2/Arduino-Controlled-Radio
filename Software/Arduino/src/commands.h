/*
Software Controlled Radio - Command Definitions
*/

#ifndef COMMANDS_H
#define COMMANDS_H

#define triggerPin      13       // pin to charge the capacitor - connected to one end of the charging resistor
#define pulseInPin      21

typedef const char * processor_t(char * cmd);
typedef processor_t * processor_p;

typedef struct {
    char cmd[4];
    processor_p processor;
} command;

const char * read_Cap(char * cmd);
processor_t process_sf;
processor_t process_sb;
processor_t process_gf;

// extern command command_list[];

#endif