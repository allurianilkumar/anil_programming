#ifndef LEXER_H
#define LEXER_H

typedef enum
{
    TOKEN_VARIABLE,
    TOKEN_PRINT,
    TOKEN_ASSIGN,
    TOKEN_END,
    TOKEN_UNKNOWN
} TokenType;

typedef struct
{
    TokenType type;
    char value[256];
} Token;

Token get_next_token(const char **input);

#endif // LEXER_H
