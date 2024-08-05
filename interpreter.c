#include "interpreter.h"
#include <stdio.h>
#include <string.h>

static void interpret_class(ASTNode *node)
{
    printf("Class definition: %s\n", node->value);
    ASTNode *method = node->left;
    while (method)
    {
        printf("Method definition: %s\n", method->value);
        method = method->next;
    }
}

static void interpret_method(ASTNode *node)
{
    printf("Method call: %s\n", node->value);
    ASTNode *arg = node->left;
    while (arg)
    {
        interpret(arg);
        arg = arg->next;
    }
}

static void interpret_function(ASTNode *node)
{
    printf("Function definition: %s\n", node->value);
    ASTNode *stmt = node->left;
    while (stmt)
    {
        interpret(stmt);
        stmt = stmt->next;
    }
}

static void interpret_function_call(ASTNode *node)
{
    printf("Function call: %s\n", node->value);
    ASTNode *arg = node->left;
    while (arg)
    {
        interpret(arg);
        arg = arg->next;
    }
}

static void interpret_assignment(ASTNode *node)
{
    printf("Assigning to: %s\n", node->value);
    ASTNode *expr = node->left;
    while (expr)
    {
        interpret(expr);
        expr = expr->next;
    }
}

static void interpret_print(ASTNode *node)
{
    ASTNode *expr = node->left;
    while (expr)
    {
        switch (expr->type)
        {
        case NODE_STRING:
            printf("%s\n", expr->value);
            break;
        case NODE_IDENTIFIER:
            printf("Variable: %s\n", expr->value);
            break;
        case NODE_ARRAY:
        {
            printf("[");
            ASTNode *elem = expr->left;
            while (elem)
            {
                interpret(elem);
                elem = elem->next;
                if (elem)
                    printf(", ");
            }
            printf("]\n");
            break;
        }
        case NODE_HASH:
        {
            printf("{");
            ASTNode *pair = expr->left;
            while (pair)
            {
                interpret(pair);
                pair = pair->next;
                if (pair)
                    printf(", ");
            }
            printf("}\n");
            break;
        }
        default:
            break;
        }
        expr = expr->next;
    }
}

void interpret(ASTNode *root)
{
    if (!root)
        return;

    switch (root->type)
    {
    case NODE_CLASS_DEF:
        interpret_class(root);
        break;
    case NODE_METHOD_DEF:
        interpret_method(root);
        break;
    case NODE_FUNCTION_DEF:
        interpret_function(root);
        break;
    case NODE_FUNCTION_CALL:
        interpret_function_call(root);
        break;
    case NODE_ASSIGN:
        interpret_assignment(root);
        break;
    case NODE_PRINT:
        interpret_print(root);
        break;
    default:
        break;
    }

    interpret(root->next);
}
