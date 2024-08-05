#ifndef PARSER_H
#define PARSER_H

typedef enum
{
    NODE_CLASS_DEF,
    NODE_METHOD_DEF,
    NODE_FUNCTION_DEF,
    NODE_FUNCTION_CALL,
    NODE_ASSIGN,
    NODE_PRINT,
    NODE_INPUT,
    NODE_STRING,
    NODE_IDENTIFIER,
    NODE_ARRAY,
    NODE_HASH
} NodeType;

typedef struct ASTNode
{
    NodeType type;
    char *value;
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *next;
} ASTNode;

ASTNode *parse(const char *input);
void free_ast(ASTNode *node);

#endif // PARSER_H
