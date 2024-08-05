#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interpreter.h"
#include "variable.h"

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

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';

        // Parse the line
        Command cmd = parse_line(line);

        // Execute the command
        execute_command(cmd, variables, &variable_count, functions, &function_count);
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
