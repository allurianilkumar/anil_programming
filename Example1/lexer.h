// lexer.h
#ifndef LEXER_H
#define LEXER_H

typedef enum
{
    TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_ASSIGN,
    TOKEN_CLASS,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_COMMA,
    TOKEN_DOT,
    TOKEN_EOF,
    TOKEN_PRINT,
    TOKEN_INPUT,
    TOKEN_DEF
} TokenType;

typedef struct
{
    TokenType type;
    char value[256];
} Token;

void init_lexer(const char *input);
Token get_next_token();

#endif // LEXER_H
