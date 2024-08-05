#ifndef VARIABLE_H
#define VARIABLE_H

typedef struct
{
    char name[256];
    char value[256];
} Variable;

int find_variable(Variable variables[], int count, const char *name);
void set_variable(Variable variables[], int *count, const char *name, const char *value);
const char *get_variable(Variable variables[], int count, const char *name);

#endif
