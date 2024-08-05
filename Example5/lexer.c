#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

// Extract a string token from input
static void extract_token_value(const char *start, char *value, size_t length)
{
    strncpy(value, start, length);
    value[length] = '\0';
}

// Get the next token from the input
Token get_next_token(const char **input)
{
    Token token;
    const char *start = *input;

    // Skip whitespace
    while (isspace(*start))
    {
        start++;
    }

    // Check for end of input
    if (*start == '\0')
    {
        token.type = TOKEN_UNKNOWN;
        return token;
    }

    // Handle specific tokens
    if (*start == '=')
    {
        token.type = TOKEN_ASSIGN;
        *input = start + 1;
        return token;
    }
    else if (strncmp(start, "print", 5) == 0 && !isalnum(start[5]))
    {
        token.type = TOKEN_PRINT;
        extract_token_value(start, token.value, 5);
        *input = start + 5;
        return token;
    }
    else if (*start == '"')
    {
        start++;
        const char *end = strchr(start, '"');
        if (end)
        {
            size_t length = end - start;
            token.type = TOKEN_STRING;
            extract_token_value(start, token.value, length);
            *input = end + 1;
        }
        else
        {
            token.type = TOKEN_UNKNOWN;
            *input = start;
        }
        return token;
    }
    else if (isalpha(*start))
    {
        const char *end = start;
        while (isalnum(*end) || *end == '_')
        {
            end++;
        }
        size_t length = end - start;
        token.type = TOKEN_IDENTIFIER;
        extract_token_value(start, token.value, length);
        *input = end;
        return token;
    }
    else
    {
        token.type = TOKEN_UNKNOWN;
        *input = start + 1;
        return token;
    }
}
