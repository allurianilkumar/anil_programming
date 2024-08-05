#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "lexer.h"
#include "variable.h"

// Initialize the parser
void parser_init(Parser *parser, const char *input)
{
    parser->input = input;
    parser->token = get_next_token(&parser->input);
}

// Parse a single command
void parse_command(Parser *parser, Variable *variables[], int *variable_count)
{
    Token token = parser->token;

    if (token.type == TOKEN_IDENTIFIER)
    {
        if (strcmp(token.value, "print") == 0)
        {
            parser->token = get_next_token(&parser->input);
            while (parser->token.type != TOKEN_UNKNOWN)
            {
                if (parser->token.type == TOKEN_STRING)
                {
                    printf("%s", parser->token.value);
                }
                else if (parser->token.type == TOKEN_IDENTIFIER)
                {
                    for (int i = 0; i < *variable_count; ++i)
                    {
                        if (strcmp(variables[i]->name, parser->token.value) == 0)
                        {
                            printf("%s", get_variable_value(variables[i], "value"));
                            break;
                        }
                    }
                }
                parser->token = get_next_token(&parser->input);
            }
        }
    }
    else if (token.type == TOKEN_IDENTIFIER)
    {
        const char *name = token.value;
        parser->token = get_next_token(&parser->input);
        if (parser->token.type == TOKEN_ASSIGN)
        {
            parser->token = get_next_token(&parser->input);
            if (parser->token.type == TOKEN_STRING)
            {
                // Assign the value to the variable
                Variable *var = create_variable(name, parser->token.value);
                variables[*variable_count] = var;
                (*variable_count)++;
            }
        }
    }
}
