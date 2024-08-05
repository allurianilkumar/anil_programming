#include "lexer.h"
#include <ctype.h>
#include <string.h>

static Token create_token(TokenType type, const char *value)
{
    Token token;
    token.type = type;
    strncpy(token.value, value, sizeof(token.value) - 1);
    token.value[sizeof(token.value) - 1] = '\0';
    return token;
}

Token get_next_token(const char **input)
{
    while (isspace(**input))
    {
        (*input)++;
    }

    if (**input == '\0')
    {
        return create_token(TOKEN_END, "");
    }

    if (strncmp(*input, "print", 5) == 0 && !isalnum((*input)[5]))
    {
        *input += 5;
        return create_token(TOKEN_PRINT, "print");
    }

    if (**input == '=')
    {
        (*input)++;
        return create_token(TOKEN_ASSIGN, "=");
    }

    if (isalpha(**input))
    {
        const char *start = *input;
        while (isalnum(**input))
        {
            (*input)++;
        }
        return create_token(TOKEN_VARIABLE, strndup(start, *input - start));
    }

    return create_token(TOKEN_UNKNOWN, "");
}
