#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

Command parse_command(Token *tokens, int token_count)
{
    Command command;
    command.type = CMD_UNKNOWN;

    if (token_count < 2)
    {
        return command;
    }

    if (tokens[0].type == TOKEN_NAME && tokens[1].type == TOKEN_EQUALS)
    {
        command.type = CMD_SET;
        strcpy(command.name, tokens[0].value);
        strcpy(command.value, tokens[2].value);
    }
    else if (tokens[0].type == TOKEN_PRINT && tokens[1].type == TOKEN_NAME)
    {
        command.type = CMD_PRINT;
        strcpy(command.name, tokens[1].value);
    }

    return command;
}
