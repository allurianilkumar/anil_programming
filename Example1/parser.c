// parser.c
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

static Token current_token;

static void next_token()
{
    current_token = get_next_token();
}

static ASTNode *new_node(NodeType type)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static ASTNode *parse_statement()
{
    if (current_token.type == TOKEN_PRINT)
    {
        next_token();
        ASTNode *node = new_node(NODE_PRINT);
        node->left = new_node(TOKEN_STRING);
        strcpy(node->left->name, current_token.value);
        next_token();
        return node;
    }
    else if (current_token.type == TOKEN_IDENTIFIER)
    {
        char var_name[256];
        strcpy(var_name, current_token.value);
        next_token();
        if (current_token.type == TOKEN_ASSIGN)
        {
            next_token();
            if (current_token.type == TOKEN_INPUT)
            {
                next_token();
                ASTNode *node = new_node(NODE_INPUT);
                node->left = new_node(TOKEN_IDENTIFIER);
                strcpy(node->left->name, var_name);
                node->right = new_node(TOKEN_STRING);
                strcpy(node->right->name, current_token.value);
                next_token();
                return node;
            }
        }
    }
    return NULL;
}

ASTNode *parse(const char *code)
{
    init_lexer(code);
    next_token();
    return parse_statement();
}

void free_ast(ASTNode *node)
{
    if (node != NULL)
    {
        free_ast(node->left);
        free_ast(node->right);
        free(node);
    }
}
