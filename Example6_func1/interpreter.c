#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "interpreter.h"
#include "variable.h"

static char *trim_whitespace(char *str)
{
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0)
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    end[1] = '\0';

    return str;
}

void execute_command(Command command, Variable *variables[], int *variable_count, Function *functions[], int *function_count)
{
    if (command.type == COMMAND_VARIABLE)
    {
        char name[256], value[256];
        if (sscanf(command.content, "%255[^=] = \"%255[^\"]\"", name, value) == 2 ||
            sscanf(command.content, "%255[^=] = [%255[^]]]", name, value) == 2 ||
            sscanf(command.content, "%255[^=] = \"%255[^\"]\"", name, value) == 2)
        {
            // Create a new variable
            Variable *var = create_variable(trim_whitespace(name), value);
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
        Function *func = malloc(sizeof(Function));
        sscanf(command.name, "%255s", func->name);
        // Extract function body
        strncpy(func->body, command.content, sizeof(func->body) - 1);
        functions[*function_count] = func;
        (*function_count)++;
    }
    else if (command.type == COMMAND_FUNCTION_CALL)
    {
        for (int i = 0; i < *function_count; ++i)
        {
            if (strcmp(functions[i]->name, command.name) == 0)
            {
                // Execute function body
                char *line = strtok(functions[i]->body, "\n");
                while (line != NULL)
                {
                    Command func_cmd = parse_line(line);
                    execute_command(func_cmd, variables, variable_count, functions, function_count);
                    line = strtok(NULL, "\n");
                }
                break;
            }
        }
    }
    else
    {
        printf("Unknown command\n");
    }
}

Command parse_line(const char *line)
{
    Command cmd;
    memset(&cmd, 0, sizeof(cmd)); // Initialize to zero

    if (strncmp(line, "print", 5) == 0)
    {
        cmd.type = COMMAND_PRINT;
        strncpy(cmd.content, line + 6, sizeof(cmd.content) - 1);
    }
    else if (strncmp(line, "def ", 4) == 0)
    {
        cmd.type = COMMAND_FUNCTION_DEF;
        sscanf(line + 4, "%255[^ {]", cmd.name);
        // Extract function body
        const char *body_start = strchr(line, '{');
        const char *body_end = strrchr(line, '}');
        if (body_start && body_end && body_end > body_start)
        {
            strncpy(cmd.content, body_start + 1, body_end - body_start - 1);
        }
    }
    else if (strncmp(line, "call ", 5) == 0)
    {
        cmd.type = COMMAND_FUNCTION_CALL;
        sscanf(line + 5, "%255s", cmd.name);
    }
    else
    {
        cmd.type = COMMAND_VARIABLE;
        strncpy(cmd.content, line, sizeof(cmd.content) - 1);
    }
    return cmd;
}
