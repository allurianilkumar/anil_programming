#include "variable.h"
#include <stdlib.h>
#include <string.h>

Variable *create_variable(const char *name, const char *value)
{
    Variable *var = (Variable *)malloc(sizeof(Variable));
    strncpy(var->name, name, MAX_VAR_NAME_LENGTH);
    strncpy(var->value, value, MAX_VAR_VALUE_LENGTH);
    return var;
}

void destroy_variable(Variable *variable)
{
    free(variable);
}

const char *get_variable_value(const Variable *variable, const char *attribute_name)
{
    // Check the attribute name and return the appropriate value
    if (strcmp(attribute_name, "value") == 0)
    {
        return variable->value;
    }
    return NULL;
}
