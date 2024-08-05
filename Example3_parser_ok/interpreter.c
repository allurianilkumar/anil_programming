#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "variable.h"

void execute_command(Command command, Variable *variables[], int *variable_count)
{
    if (strncmp(command.text, "name = ", 7) == 0)
    {
        char value[256];
        sscanf(command.text, "name = \"%255[^\"]\"", value);

        // Create or update variable
        int found = 0;
        for (int i = 0; i < *variable_count; ++i)
        {
            if (strcmp(variables[i]->name, "name") == 0)
            {
                set_variable_value(variables[i], value);
                found = 1;
                break;
            }
        }
        if (!found)
        {
            variables[*variable_count] = create_variable("name", value);
            (*variable_count)++;
        }
    }
    else if (strncmp(command.text, "print ", 6) == 0)
    {
        char var_name[256];
        sscanf(command.text, "print %255s", var_name);

        // Print the value of the variable
        int found = 0;
        for (int i = 0; i < *variable_count; ++i)
        {
            if (strcmp(variables[i]->name, var_name) == 0)
            {
                char *value = get_variable_value(variables[i]);
                if (value != NULL)
                {
                    printf("%s\n", value);
                }
                else
                {
                    printf("Value for variable '%s' is NULL\n", var_name);
                }
                found = 1;
                break;
            }
        }
        if (!found)
        {
            printf("Variable '%s' not found\n", var_name);
        }
    }
    else
    {
        printf("Unknown command: %s\n", command.text);
    }
}
