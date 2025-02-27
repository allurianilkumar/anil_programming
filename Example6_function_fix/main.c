#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interpreter.h"
#include "variable.h"

Command parse_line(const char *line)
{
    Command cmd;
    memset(&cmd, 0, sizeof(cmd)); // Initialize to zero

    if (strncmp(line, "def", 3) == 0)
    {
        cmd.type = COMMAND_FUNCTION_DEF;
        sscanf(line + 4, "%255s { %[^\n] }", cmd.name, cmd.content);
    }
    else if (line[strlen(line) - 1] == ')')
    {
        cmd.type = COMMAND_FUNCTION_CALL;
        sscanf(line, "%255s(", cmd.name);
    }
    else if (strncmp(line, "print", 5) == 0)
    {
        cmd.type = COMMAND_PRINT;
        strncpy(cmd.content, line + 6, sizeof(cmd.content) - 1);
    }
    else
    {
        cmd.type = COMMAND_VARIABLE;
        strncpy(cmd.content, line, sizeof(cmd.content) - 1);
    }
    return cmd;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <script.anil>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file");
        return 1;
    }

    Variable *variables[256];
    int variable_count = 0;

    Function *functions[256];
    int function_count = 0;

    Variable *local_vars[256];
    int local_var_count = 0;

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';

        // Parse the line
        Command cmd = parse_line(line);

        // Execute the command
        execute_command(cmd, variables, &variable_count, functions, &function_count, local_vars, &local_var_count);
    }

    fclose(file);

    // Cleanup all variables
    for (int i = 0; i < variable_count; ++i)
    {
        destroy_variable(variables[i]);
    }

    // Cleanup all functions
    for (int i = 0; i < function_count; ++i)
    {
        free(functions[i]);
    }

    return 0;
}
