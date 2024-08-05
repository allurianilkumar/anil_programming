#include <stdlib.h>
#include <string.h>
#include "variable.h"

// Create a new variable
Variable *create_variable(const char *name, const char *value)
{
    Variable *var = (Variable *)malloc(sizeof(Variable));
    if (var)
    {
        var->name = strdup(name);
        var->value = strdup(value);
    }
    return var;
}

// Set the value of an existing variable
void set_variable_value(Variable *var, const char *value)
{
    if (var->value)
    {
        free(var->value);
    }
    var->value = strdup(value);
}

// Get the value of a variable
char *get_variable_value(const Variable *var)
{
    return var->value;
}

// Destroy a variable and free its resources
void destroy_variable(Variable *var)
{
    if (var)
    {
        if (var->name)
        {
            free(var->name);
        }
        if (var->value)
        {
            free(var->value);
        }
        free(var);
    }
}
