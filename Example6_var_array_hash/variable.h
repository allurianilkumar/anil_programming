#ifndef VARIABLE_H
#define VARIABLE_H

#define MAX_VAR_NAME_LENGTH 256
#define MAX_VAR_VALUE_LENGTH 256

typedef struct
{
    char name[MAX_VAR_NAME_LENGTH];
    char value[MAX_VAR_VALUE_LENGTH];
} Variable;

Variable *create_variable(const char *name, const char *value);
void destroy_variable(Variable *variable);
const char *get_variable_value(const Variable *variable, const char *attribute_name);

#endif // VARIABLE_H
