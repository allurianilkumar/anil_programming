#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "variable.h"

typedef struct
{
    Token token;
    const char *input;
} Parser;

void parser_init(Parser *parser, const char *input);
void parse_command(Parser *parser, Variable *variables[], int *variable_count);

#endif // PARSER_H
