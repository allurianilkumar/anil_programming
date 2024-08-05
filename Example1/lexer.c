// lexer.c
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"

static const char *src;
static int pos = 0;
static int length = 0;

void init_lexer(const char *input)
{
    src = input;
    pos = 0;
    length = strlen(input);
}

Token get_next_token()
{
    Token token;
    token.value[0] = '\0';

    while (pos < length && isspace(src[pos]))
    {
        pos++;
    }

    if (pos >= length)
    {
        token.type = TOKEN_EOF;
        return token;
    }

    char current = src[pos];

    if (isalpha(current))
    {
        int start = pos;
        while (pos < length && (isalnum(src[pos]) || src[pos] == '_'))
        {
            pos++;
        }
        strncpy(token.value, src + start, pos - start);
        token.value[pos - start] = '\0';

        if (strcmp(token.value, "Class") == 0)
        {
            token.type = TOKEN_CLASS;
        }
        else if (strcmp(token.value, "print") == 0)
        {
            token.type = TOKEN_PRINT;
        }
        else if (strcmp(token.value, "input") == 0)
        {
            token.type = TOKEN_INPUT;
        }
        else if (strcmp(token.value, "def") == 0)
        {
            token.type = TOKEN_DEF;
        }
        else
        {
            token.type = TOKEN_IDENTIFIER;
        }
    }
    else if (current == '=')
    {
        token.type = TOKEN_ASSIGN;
        token.value[0] = current;
        token.value[1] = '\0';
        pos++;
    }
    else if (current == '{')
    {
        token.type = TOKEN_LBRACE;
        token.value[0] = current;
        token.value[1] = '\0';
        pos++;
    }
    else if (current == '}')
    {
        token.type = TOKEN_RBRACE;
        token.value[0] = current;
        token.value[1] = '\0';
        pos++;
    }
    else if (current == '(')
    {
        token.type = TOKEN_LPAREN;
        token.value[0] = current;
        token.value[1] = '\0';
        pos++;
    }
    else if (current == ')')
    {
        token.type = TOKEN_RPAREN;
        token.value[0] = current;
        token.value[1] = '\0';
        pos++;
    }
    else if (current == ',')
    {
        token.type = TOKEN_COMMA;
        token.value[0] = current;
        token.value[1] = '\0';
        pos++;
    }
    else if (current == '.')
    {
        token.type = TOKEN_DOT;
        token.value[0] = current;
        token.value[1] = '\0';
        pos++;
    }
    else if (current == '\"')
    {
        token.type = TOKEN_STRING;
        int start = ++pos;
        while (pos < length && src[pos] != '\"')
        {
            pos++;
        }
        strncpy(token.value, src + start, pos - start);
        token.value[pos - start] = '\0';
        pos++;
    }
    else if (isdigit(current))
    {
        token.type = TOKEN_NUMBER;
        int start = pos;
        while (pos < length && isdigit(src[pos]))
        {
            pos++;
        }
        strncpy(token.value, src + start, pos - start);
        token.value[pos - start] = '\0';
    }
    else
    {
        token.type = TOKEN_EOF;
    }

    return token;
}
