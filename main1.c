#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

// Function to read the entire content of a file into a string
char* read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = malloc(length + 1);
    if (!content) {
        perror("Could not allocate memory");
        fclose(file);
        return NULL;
    }

    fread(content, 1, length, file);
    fclose(file);
    content[length] = '\0';

    return content;
}

int main() {
    // Read the content of the test.anil file
    char *code = read_file("test.anil");
    if (!code) {
        return 1; // Exit if file reading failed
    }

    // Parse and interpret the code
    ASTNode *ast = parse(code);
    while (ast != NULL) {
        interpret(ast);
        ast = parse(NULL);  // Assuming the lexer/parser was updated to return a NULL node when done
    }

    // Clean up
    free(code);
    return 0;
}
