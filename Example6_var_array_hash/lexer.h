#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKEN_LENGTH 256
#define MAX_VARIABLE_NAME_LENGTH 256
#define MAX_VALUE_LENGTH 256

typedef enum
{
    TOKEN_UNKNOWN,
    TOKEN_ASSIGN,
    TOKEN_PRINT,
    TOKEN_STRING,
    TOKEN_IDENTIFIER
} TokenType;

typedef struct
{
    TokenType type;
    char value[MAX_VALUE_LENGTH];
} Token;

Token get_next_token(const char **input);

#endif // LEXER_H
