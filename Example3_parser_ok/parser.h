#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef enum
{
    CMD_SET,
    CMD_PRINT,
    CMD_UNKNOWN
} CommandType;

typedef struct
{
    CommandType type;
    char name[256];
    char value[256];
} Command;

Command parse_command(Token *tokens, int token_count);

#endif // PARSER_H
