// interpreter.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "lexer.h"
#include "parser.h"
#include "variable.h"

static Variable variables[256];
static int variable_count = 0;

void interpret(ASTNode *node)
{
    if (node == NULL)
        return;

    switch (node->type)
    {
    case NODE_PRINT:
        printf("%s\n", node->left->name);
        break;
    case NODE_INPUT:
    {
        printf("%s", node->right->name);
        char input[256];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        set_variable(variables, &variable_count, node->left->name, input);
        break;
    }
    default:
        break;
    }
}
