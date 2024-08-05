// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include "variable.h"

// Function to read the content of a file into a buffer
char *read_file(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(length + 1);
    if (!buffer)
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);

    return buffer;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename.anil>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *ext = strrchr(filename, '.');
    if (!ext || strcmp(ext, ".anil") != 0)
    {
        fprintf(stderr, "Invalid file type. Use <filename.anil> only.\n");
        return 1;
    }

    char *code = read_file(filename);

    ASTNode *ast = parse(code);
    interpret(ast);

    free_ast(ast);
    free(code);

    return 0;
}
