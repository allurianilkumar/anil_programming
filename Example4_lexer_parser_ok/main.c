#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "interpreter.h"

#define MAX_VARIABLES 256

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

    Variable *variables[MAX_VARIABLES];
    int variable_count = 0;

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';

        Command cmd;
        if (parse_command(line, &cmd))
        {
            execute_command(&cmd, variables, &variable_count);
        }
        else
        {
            printf("Failed to parse command: %s\n", line);
        }
    }

    fclose(file);

    // Cleanup all variables
    for (int i = 0; i < variable_count; ++i)
    {
        destroy_variable(variables[i]);
    }

    return 0;
}
