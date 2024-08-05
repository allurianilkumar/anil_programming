#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "interpreter.h"
#include "variable.h"

// Print array values
static void print_array(const char *array_str)
{
    printf("[");
    const char *start = array_str + 1;    // Skip the opening '['
    const char *end = strchr(start, ']'); // Find the closing ']'
    if (end)
    {
        const char *current = start;
        while (current < end)
        {
            // Extract value
            const char *comma = strchr(current, ',');
            if (comma && comma < end)
            {
                printf("%.*s,", (int)(comma - current), current);
                current = comma + 1;
            }
            else
            {
                printf("%.*s", (int)(end - current), current);
                break;
            }
        }
    }
    printf("]");
}

// Print hash values
static void print_hash(const char *hash_str)
{
    printf("{");
    const char *start = hash_str + 1;     // Skip the opening '{'
    const char *end = strchr(start, '}'); // Find the closing '}'
    if (end)
    {
        const char *current = start;
        while (current < end)
        {
            // Extract key
            const char *colon = strchr(current, ':');
            if (colon && colon < end)
            {
                printf("\"%.*s\":", (int)(colon - current), current);
                current = colon + 1;

                // Extract value
                const char *comma = strchr(current, ',');
                if (comma && comma < end)
                {
                    printf("%.*s,", (int)(comma - current), current);
                    current = comma + 1;
                }
                else
                {
                    printf("%.*s", (int)(end - current), current);
                    break;
                }
            }
        }
    }
    printf("}");
}

void execute_command(Command command, Variable *variables[], int *variable_count)
{
    if (command.type == COMMAND_VARIABLE)
    {
        char name[256], value[1024];
        if (sscanf(command.content, "%255s = %1023[^\n]", name, value) == 2)
        {
            // Create a new variable
            Variable *var = create_variable(name, value);
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
                    putchar(*print_content++);
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
                        const char *value = get_variable_value(variables[i], "value");
                        if (value[0] == '[')
                        {
                            // Handle array
                            print_array(value);
                        }
                        else if (value[0] == '{')
                        {
                            // Handle hash
                            print_hash(value);
                        }
                        else
                        {
                            printf("%s", value);
                        }
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
                putchar(*print_content++);
            }
        }
        putchar('\n');
    }
    else
    {
        printf("Unknown command\n");
    }
}
