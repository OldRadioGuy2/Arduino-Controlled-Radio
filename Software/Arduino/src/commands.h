/*
Software Controlled Radio - Command Definitions
*/

#ifndef COMMANDS_H
#define COMMANDS_H

typedef struct {
    char * name;
    char * (*processor)(char * cmd_line);
} command;

char * process_sf(char * cmd_line);
char * process_sb(char * cmd_line);

#define COMMAND_COUNT
command command_list []= {
    {"SF", process_sf },    //Set Frequency: SF,float_frequency,units
    {"SB", process_sb },    //Set Band: SB,float_lower_limit, float_upper_limit, units
}


#endif