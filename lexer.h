#ifndef LEXER_H
#define LEXER_H

typedef enum
{
    TOKEN_CLASS,
    TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_ASSIGN,
    TOKEN_PRINT,
    TOKEN_INPUT,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_COMMA,
    TOKEN_DOT,
    TOKEN_COLON,
    TOKEN_SEMICOLON,
    TOKEN_EOF
} TokenType;

typedef struct
{
    TokenType type;
    char *value;
} Token;

Token *get_next_token();
void free_token(Token *token);
void set_input(const char *input);

#endif // LEXER_H
