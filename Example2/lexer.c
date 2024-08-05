#include <ctype.h>
#include <string.h>
#include "lexer.h"

Token get_next_token(const char **code)
{
    while (isspace(**code))
    {
        (*code)++;
    }

    Token token = {TOKEN_UNKNOWN, {0}};

    if (strncmp(*code, "print", 5) == 0 && isspace((*code)[5]))
    {
        token.type = TOKEN_PRINT;
        *code += 5;
    }
    else if (**code == '=')
    {
        token.type = TOKEN_ASSIGN;
        (*code)++;
    }
    else if (**code == '\0' || **code == '\n')
    {
        token.type = TOKEN_END;
    }
    else if (**code == '"' || **code == '\'')
    {
        char quote = *(*code)++;
        char *val_ptr = token.value;
        while (**code && **code != quote)
        {
            *val_ptr++ = *(*code)++;
        }
        if (**code == quote)
        {
            (*code)++;
        }
        token.type = TOKEN_STRING;
    }
    else if (isalpha(**code) || **code == '_')
    {
        char *val_ptr = token.value;
        while (isalnum(**code) || **code == '_')
        {
            *val_ptr++ = *(*code)++;
        }
        token.type = TOKEN_IDENTIFIER;
    }

    return token;
}
