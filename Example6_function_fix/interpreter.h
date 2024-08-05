#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "variable.h" // Include the variable header file

typedef enum
{
    COMMAND_VARIABLE,
    COMMAND_PRINT,
    COMMAND_FUNCTION_DEF,
    COMMAND_FUNCTION_CALL
} CommandType;

typedef struct
{
    CommandType type;
    char name[256];
    char content[1024];
} Command;

typedef struct
{
    char name[256];
    char body[1024];
} Function;

Command parse_line(const char *line);
void execute_command(Command command, Variable *variables[], int *variable_count, Function *functions[], int *function_count, Variable *local_vars[], int *local_var_count);

#endif // INTERPRETER_H
