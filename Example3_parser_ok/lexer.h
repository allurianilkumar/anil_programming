#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_NAME,
    TOKEN_EQUALS,
    TOKEN_PRINT,
    TOKEN_STRING,
    TOKEN_EOF,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char value[256];
} Token;

Token get_next_token(FILE *file);

#endif // LEXER_H
