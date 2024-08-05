#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "variable.h"
#include "interpreter.h"
#include "command.h"

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

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';

        // Convert line to Command
        Command cmd;
        strncpy(cmd.text, line, sizeof(cmd.text) - 1);
        cmd.text[sizeof(cmd.text) - 1] = '\0';

        // Call execute_command with the Command type
        execute_command(cmd, variables, &variable_count);
    }

    fclose(file);

    // Cleanup all variables
    for (int i = 0; i < variable_count; ++i)
    {
        destroy_variable(variables[i]);
    }

    return 0;
}
