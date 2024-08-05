#ifndef VARIABLE_H
#define VARIABLE_H

// Define the Variable structure
typedef struct
{
    char *name;
    char *value;
} Variable;

// Function prototypes
Variable *create_variable(const char *name, const char *value);
void set_variable_value(Variable *var, const char *value);
char *get_variable_value(const Variable *var);
void destroy_variable(Variable *var);

#endif // VARIABLE_H
