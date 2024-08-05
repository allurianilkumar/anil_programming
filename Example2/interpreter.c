#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "parser.h"
#include "variable.h"
#include "interpreter.h"

void interpret(ASTNode *node, Variable variables[], int *variable_count)
{
    if (!node)
        return;

    if (strcmp(node->type, "print") == 0)
    {
        if (node->left && strcmp(node->left->type, "string") == 0)
        {
            char output[256];
            strcpy(output, node->left->value);
            replace_variables(output, variables, *variable_count);
            printf("%s\n", output);
        }
        else if (node->left && strcmp(node->left->type, "identifier") == 0)
        {
            const char *var_value = get_variable(variables, *variable_count, node->left->value);
            if (var_value)
            {
                printf("%s\n", var_value);
            }
            else
            {
                printf("Variable not found: %s\n", node->left->value);
            }
        }
    }
    else if (strcmp(node->type, "assign") == 0)
    {
        if (node->left && node->right && strcmp(node->left->type, "identifier") == 0 && strcmp(node->right->type, "string") == 0)
        {
            set_variable(variables, variable_count, node->left->value, node->right->value);
        }
    }

    interpret(node->right, variables, variable_count);
}

void replace_variables(char *str, Variable variables[], int count)
{
    char buffer[1024];
    char *p = str;
    char *b = buffer;

    while (*p)
    {
        if (*p == '#')
        {
            p++;
            char var_name[256];
            char *vn = var_name;

            while (*p && (isalnum(*p) || *p == '_'))
            {
                *vn++ = *p++;
            }
            *vn = '\0';

            const char *var_value = get_variable(variables, count, var_name);
            if (var_value)
            {
                b += sprintf(b, "%s", var_value);
            }
            else
            {
                b += sprintf(b, "#%s", var_name);
            }
        }
        else
        {
            *b++ = *p++;
        }
    }
    *b = '\0';
    strcpy(str, buffer);
}
