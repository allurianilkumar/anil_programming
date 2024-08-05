#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "variable.h"

// Define the type of command
typedef enum
{
    COMMAND_VARIABLE,
    COMMAND_PRINT
} CommandType;

// Define the Command struct
typedef struct
{
    CommandType type;
    char content[1024]; // Adjust size as needed
} Command;

// Function prototypes
void execute_command(Command command, Variable *variables[], int *variable_count);

#endif // INTERPRETER_H
