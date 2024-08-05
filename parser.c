#include "parser.h"
#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static Token *current_token;

static void advance_token()
{
    free_token(current_token);
    current_token = get_next_token();
}

static ASTNode *create_node(NodeType type, const char *value)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = type;
    node->value = value ? strdup(value) : NULL;
    node->left = node->right = node->next = NULL;
    return node;
}

static void free_node(ASTNode *node)
{
    if (node->value)
        free(node->value);
    free(node);
}

ASTNode *parse(const char *input)
{
    if (input)
        set_input(input);
    advance_token();

    ASTNode *root = NULL;
    ASTNode **current = &root;

    while (current_token->type != TOKEN_EOF)
    {
        ASTNode *node = NULL;

        if (current_token->type == TOKEN_CLASS)
        {
            advance_token();
            if (current_token->type != TOKEN_IDENTIFIER)
            {
                fprintf(stderr, "Expected class name\n");
                exit(1);
            }
            node = create_node(NODE_CLASS_DEF, current_token->value);
            advance_token();
            if (current_token->type != TOKEN_LBRACE)
            {
                fprintf(stderr, "Expected '{'\n");
                exit(1);
            }
            advance_token();
            while (current_token->type != TOKEN_RBRACE)
            {
                if (current_token->type == TOKEN_IDENTIFIER)
                {
                    char *method_name = strdup(current_token->value);
                    advance_token();
                    if (current_token->type == TOKEN_LPAREN)
                    {
                        node->left = create_node(NODE_METHOD_DEF, method_name);
                        advance_token();
                        while (current_token->type != TOKEN_RPAREN)
                        {
                            // parse parameters
                            advance_token();
                        }
                        advance_token(); // Skip closing parenthesis
                    }
                    else
                    {
                        fprintf(stderr, "Expected '('\n");
                        exit(1);
                    }
                }
                advance_token();
            }
        }

        *current = node;
        current = &node->next;

        advance_token();
    }

    return root;
}

void free_ast(ASTNode *node)
{
    while (node)
    {
        ASTNode *next = node->next;
        free_node(node);
        node = next;
    }
}
