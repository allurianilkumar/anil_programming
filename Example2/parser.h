#ifndef PARSER_H
#define PARSER_H

typedef struct ASTNode
{
    char type[32];
    char value[256];
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

ASTNode *parse(const char *code);
void free_ast(ASTNode *node);

#endif
