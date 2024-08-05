#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "lexer.h"

// Function to create a new AST node
ASTNode *create_node(const char *type, const char *value)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    strcpy(node->type, type);
    strcpy(node->value, value);
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Recursive descent parser
ASTNode *parse_expression(const char **code)
{
    Token token = get_next_token(code);

    if (token.type == TOKEN_IDENTIFIER || token.type == TOKEN_STRING)
    {
        ASTNode *node = create_node(token.type == TOKEN_IDENTIFIER ? "identifier" : "string", token.value);

        token = get_next_token(code);
        if (token.type == TOKEN_ASSIGN)
        {
            ASTNode *assign_node = create_node("assign", "=");
            assign_node->left = node;
            assign_node->right = parse_expression(code);
            return assign_node;
        }

        return node;
    }

    return NULL;
}

ASTNode *parse_statement(const char **code)
{
    Token token = get_next_token(code);

    if (token.type == TOKEN_PRINT)
    {
        ASTNode *node = create_node("print", "print");
        node->left = parse_expression(code);
        return node;
    }
    else
    {
        const char *cursor = *code;
        ASTNode *node = parse_expression(&cursor);
        if (node)
        {
            *code = cursor;
            return node;
        }
    }

    return NULL;
}

ASTNode *parse(const char *code)
{
    ASTNode *root = NULL;
    ASTNode *current = NULL;

    while (*code)
    {
        ASTNode *stmt = parse_statement(&code);

        if (!root)
        {
            root = stmt;
        }
        else
        {
            current->right = stmt;
        }
        current = stmt;

        while (*code && *code != '\n')
        {
            code++;
        }

        if (*code == '\n')
        {
            code++;
        }
    }

    return root;
}

void free_ast(ASTNode *node)
{
    if (node)
    {
        free_ast(node->left);
        free_ast(node->right);
        free(node);
    }
}
