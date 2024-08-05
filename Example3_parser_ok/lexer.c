#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

Token get_next_token(FILE *file)
{
    Token token;
    int c = fgetc(file);

    while (isspace(c))
    {
        c = fgetc(file);
    }

    if (c == EOF)
    {
        token.type = TOKEN_EOF;
        return token;
    }

    if (isalpha(c))
    {
        ungetc(c, file);
        fscanf(file, "%255s", token.value);
        token.type = TOKEN_NAME;
        return token;
    }

    if (c == '=')
    {
        token.type = TOKEN_EQUALS;
        strcpy(token.value, "=");
        return token;
    }

    if (c == 'p' && (c = fgetc(file)) == 'r' && (c = fgetc(file)) == 'i' && (c = fgetc(file)) == 'n' && (c = fgetc(file)) == 't')
    {
        token.type = TOKEN_PRINT;
        strcpy(token.value, "print");
        return token;
    }

    if (c == '"')
    {
        int i = 0;
        while ((c = fgetc(file)) != '"' && c != EOF)
        {
            if (i < sizeof(token.value) - 1)
            {
                token.value[i++] = c;
            }
        }
        token.value[i] = '\0';
        token.type = TOKEN_STRING;
        return token;
    }

    token.type = TOKEN_UNKNOWN;
    token.value[0] = (char)c;
    token.value[1] = '\0';
    return token;
}
