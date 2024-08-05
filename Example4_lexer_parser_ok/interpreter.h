#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "variable.h"

typedef struct
{
    char variable_name[256];
    char value[256];
} Command;

void execute_command(const Command *cmd, Variable *variables[], int *variable_count);

#endif // INTERPRETER_H
