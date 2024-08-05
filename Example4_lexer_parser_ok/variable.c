#include "variable.h"
#include <stdlib.h>
#include <string.h>

Variable *create_variable(const char *name, const char *value)
{
    Variable *var = (Variable *)malloc(sizeof(Variable));
    strncpy(var->name, name, sizeof(var->name));
    strncpy(var->value, value, sizeof(var->value));
    return var;
}

void destroy_variable(Variable *variable)
{
    free(variable);
}

void set_value(Variable *variable, const char *value)
{
    strncpy(variable->value, value, sizeof(variable->value));
}

const char *get_value(const Variable *variable)
{
    // Create a buffer to store the value without quotes
    static char buffer[256];
    size_t len = strlen(variable->value);

    // Remove quotes if they are present
    if (len > 1 && variable->value[0] == '"' && variable->value[len - 1] == '"')
    {
        strncpy(buffer, variable->value + 1, len - 2);
        buffer[len - 2] = '\0';
    }
    else
    {
        strncpy(buffer, variable->value, sizeof(buffer));
    }

    return buffer;
}
