#include "parser.h"
#include <stdio.h>
#include <string.h>

int parse_command(const char *line, Command *cmd)
{
    if (strstr(line, "=") != NULL)
    {
        // Assignment command
        sscanf(line, "%255s = %255[^\n]", cmd->variable_name, cmd->value);
        return 1;
    }
    else if (strstr(line, "print") != NULL)
    {
        // Print command
        sscanf(line, "print %255[^\n]", cmd->variable_name);
        cmd->value[0] = '\0';
        return 1;
    }
    return 0;
}
