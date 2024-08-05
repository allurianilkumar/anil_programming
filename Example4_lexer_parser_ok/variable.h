#ifndef VARIABLE_H
#define VARIABLE_H

typedef struct
{
    char name[256];
    char value[256];
} Variable;

Variable *create_variable(const char *name, const char *value);
void destroy_variable(Variable *var);
const char *get_variable_value(const Variable *var);

#endif // VARIABLE_H
