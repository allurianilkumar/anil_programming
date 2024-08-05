#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

// Function to read the content of a file into a buffer
char *read_file(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // Seek to the end of the file to determine the size
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the buffer
    char *buffer = (char *)malloc(length + 1);
    if (!buffer)
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    // Read the file into the buffer and null-terminate it
    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    // Close the file
    fclose(file);

    return buffer;
}

int main()
{
    // Read the content of test.anil into a buffer
    char *code = read_file("test1.anil");

    // Parse the code
    ASTNode *ast = parse(code);

    // Interpret the AST
    interpret(ast);

    // Free the AST and the buffer
    free_ast(ast);
    free(code);

    return 0;
}
