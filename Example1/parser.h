// parser.h
#ifndef PARSER_H
#define PARSER_H

typedef enum
{
    NODE_CLASS,
    NODE_FUNCTION,
    NODE_ASSIGN,
    NODE_PRINT,
    NODE_INPUT,
    NODE_CALL
} NodeType;

typedef struct ASTNode
{
    NodeType type;
    char name[256];
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

ASTNode *parse(const char *code);
void free_ast(ASTNode *node);

#endif // PARSER_H
