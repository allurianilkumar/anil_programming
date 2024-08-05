#ifndef LEXER_H
#define LEXER_H

typedef enum
{
    TOKEN_PRINT,
    TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_ASSIGN,
    TOKEN_END,
    TOKEN_UNKNOWN
} TokenType;

typedef struct
{
    TokenType type;
    char value[256];
} Token;

Token get_next_token(const char **code);

#endif
