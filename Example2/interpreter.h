#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "variable.h"
#include "parser.h"

void interpret(ASTNode *node, Variable variables[], int *variable_count);
void replace_variables(char *str, Variable variables[], int count);

#endif
