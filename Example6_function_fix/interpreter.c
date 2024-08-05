#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "interpreter.h"
#include "variable.h"

// Helper function to trim whitespace
static char *trim_whitespace(char *str)
{
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0) // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // Write new null terminator
    *(end + 1) = 0;

    return str;
}

void execute_command(Command command, Variable *variables[], int *variable_count, Function *functions[], int *function_count, Variable *local_vars[], int *local_var_count)
{
    if (command.type == COMMAND_VARIABLE)
    {
        char name[256], value[1024];

        // Check for different assignment formats
        if (sscanf(command.content, "%255[^=] = \"%1023[^\"]\"", name, value) == 2 ||
            sscanf(command.content, "%255[^=] = [%1023[^\\]]]", name, value) == 2 || // Corrected escape sequence
            sscanf(command.content, "%255[^=] = %1023s", name, value) == 2)
        {
            // Trim whitespace from name
            char *trimmed_name = trim_whitespace(name);

            // Create a new variable
            Variable *var = create_variable(trimmed_name, value);
            variables[*variable_count] = var;
            (*variable_count)++;
        }
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
                    for (int i = 0; i < *local_var_count; ++i)
                    {
                        if (strcmp(local_vars[i]->name, var_name) == 0)
                        {
                            printf("%s", get_variable_value(local_vars[i], "value"));
                            found = 1;
                            break;
                        }
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
    else if (command.type == COMMAND_FUNCTION_DEF)
    {
        Function func;
        sscanf(command.name, "%255s", func.name);
        strncpy(func.body, command.content, sizeof(func.body) - 1);
        func.body[sizeof(func.body) - 1] = '\0';

        functions[*function_count] = malloc(sizeof(Function));
        *functions[*function_count] = func;
        (*function_count)++;
    }
    else if (command.type == COMMAND_FUNCTION_CALL)
    {
        for (int i = 0; i < *function_count; ++i)
        {
            if (strcmp(functions[i]->name, command.name) == 0)
            {
                Command func_cmd = parse_line(functions[i]->body);
                execute_command(func_cmd, variables, variable_count, functions, function_count, local_vars, local_var_count);
                break;
            }
        }
    }
    else
    {
        printf("Unknown command\n");
    }
}
