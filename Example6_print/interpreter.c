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
        char *print_content = command.content;

        while (*print_content)
        {
            if (*print_content == '"')
            {
                // Print string literal
                print_content++;
                while (*print_content && *print_content != '"')
                {
                    putchar(*print_content);
                    print_content++;
                }
                if (*print_content == '"')
                {
                    print_content++;
                }
            }
            else if (isalnum(*print_content) || *print_content == '_')
            {
                // Print variable value
                char var_name[256];
                int len = 0;
                while (isalnum(*print_content) || *print_content == '_')
                {
                    var_name[len++] = *print_content++;
                }
                var_name[len] = '\0';

                int found = 0;
                for (int i = 0; i < *variable_count; ++i)
                {
                    if (strcmp(variables[i]->name, var_name) == 0)
                    {
                        printf("%s", get_variable_value(variables[i], "value"));
                        found = 1;
                        break;
                    }
                }
                if (!found)
                {
                    printf("Variable not found: %s", var_name);
                }
            }
            else if (*print_content == ',')
            {
                // Handle comma separator
                print_content++;
                printf(" ");
            }
            else if (*print_content == '\\' && *(print_content + 1) == 'n')
            {
                // Handle newline character
                print_content += 2;
                printf("\n");
            }
            else
            {
                putchar(*print_content);
                print_content++;
            }
        }
        putchar('\n');
    }
    else
    {
        printf("Unknown command\n");
    }
}
