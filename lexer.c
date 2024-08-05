#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *input;
static size_t pos = 0;
static size_t input_len;

void set_input(const char *src)
{
    input = src;
    pos = 0;
    input_len = strlen(src);
}

static char peek()
{
    if (pos >= input_len)
        return '\0';
    return input[pos];
}

static char advance()
{
    if (pos >= input_len)
        return '\0';
    return input[pos++];
}

static Token *create_token(TokenType type, const char *value)
{
    Token *token = (Token *)malloc(sizeof(Token));
    token->type = type;
    token->value = strdup(value);
    return token;
}

static void skip_whitespace()
{
    while (isspace(peek()))
        advance();
}

static Token *lex_identifier()
{
    size_t start = pos;
    while (isalnum(peek()) || peek() == '_')
        advance();
    size_t len = pos - start;
    char *value = (char *)malloc(len + 1);
    strncpy(value, input + start, len);
    value[len] = '\0';
    return create_token(TOKEN_IDENTIFIER, value);
}

static Token *lex_string()
{
    advance(); // Skip opening quote
    size_t start = pos;
    while (peek() != '"' && peek() != '\0')
        advance();
    size_t len = pos - start;
    char *value = (char *)malloc(len + 1);
    strncpy(value, input + start, len);
    value[len] = '\0';
    advance(); // Skip closing quote
    return create_token(TOKEN_STRING, value);
}

Token *get_next_token()
{
    skip_whitespace();

    char c = peek();
    if (c == '\0')
        return create_token(TOKEN_EOF, "");

    if (isalpha(c) || c == '_')
        return lex_identifier();
    if (c == '"')
        return lex_string();

    switch (c)
    {
    case '=':
        advance();
        return create_token(TOKEN_ASSIGN, "=");
    case '(':
        advance();
        return create_token(TOKEN_LPAREN, "(");
    case ')':
        advance();
        return create_token(TOKEN_RPAREN, ")");
    case '{':
        advance();
        return create_token(TOKEN_LBRACE, "{");
    case '}':
        advance();
        return create_token(TOKEN_RBRACE, "}");
    case ',':
        advance();
        return create_token(TOKEN_COMMA, ",");
    case '.':
        advance();
        return create_token(TOKEN_DOT, ".");
    case ':':
        advance();
        return create_token(TOKEN_COLON, ":");
    case ';':
        advance();
        return create_token(TOKEN_SEMICOLON, ";");
    default:
        fprintf(stderr, "Unexpected character: %c\n", c);
        exit(1);
    }

    return NULL; // Should not reach here
}

void free_token(Token *token)
{
    if (token->value)
        free(token->value);
    free(token);
}
