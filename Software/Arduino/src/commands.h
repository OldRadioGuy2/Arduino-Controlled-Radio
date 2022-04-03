/*
Software Controlled Radio - Command Definitions
*/

#ifndef COMMANDS_H
#define COMMANDS_H

typedef char* (* processor_p)(char * cmd_line) ;
typedef char* processor_t(char * cmd_line) ;


typedef struct {
    char cmd[3];
    processor_p processor;
} command;

processor_t process_sf;
processor_t process_sb;
processor_t process_gf;

command command_list []= {
    {"SF", &process_sf },    //Set Frequency: SF,float_frequency (KHz)
    {"SB", &process_sb },    //Set Band: SB,float_lower_limit, float_upper_limit 
    {"GF", &process_gf}      //Get Current Frequency: GF. Returns float frequency in KHz
};


#endif