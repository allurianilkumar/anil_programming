#include "interpreter.h"
#include <stdio.h>
#include <string.h>

void execute_command(const Command *cmd, Variable *variables[], int *variable_count)
{
    if (strlen(cmd->value) > 0)
    {
        // Assignment command
        for (int i = 0; i < *variable_count; ++i)
        {
            if (strcmp(variables[i]->name, cmd->variable_name) == 0)
            {
                set_value(variables[i], cmd->value);
                return;
            }
        }
        // Create new variable if not found
        Variable *var = create_variable(cmd->variable_name, cmd->value);
        variables[*variable_count] = var;
        (*variable_count)++;
    }
    else
    {
        // Print command
        for (int i = 0; i < *variable_count; ++i)
        {
            if (strcmp(variables[i]->name, cmd->variable_name) == 0)
            {
                printf("%s\n", get_value(variables[i]));
                return;
            }
        }
        printf("Variable not found\n");
    }
}
