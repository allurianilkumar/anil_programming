#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "variable.h"
#include "command.h" // Include command.h to use Command type

void execute_command(Command command, Variable *variables[], int *variable_count);

#endif // INTERPRETER_H
