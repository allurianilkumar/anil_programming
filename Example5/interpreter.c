#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "interpreter.h"
#include "variable.h"

void execute_command(Command command, Variable *variables[], int *variable_count)
{
    if (command.type == COMMAND_VARIABLE)
    {
        char name[256], value[256];
        sscanf(command.content, "%255s = \"%255[^\"]\"", name, value);

        // Create a new variable
        Variable *var = create_variable(name, value);
        variables[*variable_count] = var;
        (*variable_count)++;
    }
    else if (command.type == COMMAND_PRINT)
    {
        char print_content[1024];
        strncpy(print_content, command.content, sizeof(print_content));

        char *token = strtok(print_content, " \n");
        while (token != NULL)
        {
            if (token[0] == '"')
            {
                // Print string literal
                printf("%s ", token + 1); // Skip the opening quote
            }
            else
            {
                // Print variable value
                int found = 0;
                for (int i = 0; i < *variable_count; ++i)
                {
                    if (strcmp(variables[i]->name, token) == 0)
                    {
                        printf("%s ", get_variable_value(variables[i], "value"));
                        found = 1;
                        break;
                    }
                }
                if (!found)
                {
                    printf("Variable not found ");
                }
            }
            token = strtok(NULL, " \n");
        }
        printf("\n");
    }
    else
    {
        printf("Unknown command\n");
    }
}
