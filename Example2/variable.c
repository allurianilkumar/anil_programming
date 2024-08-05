#include <string.h>
#include "variable.h"

int find_variable(Variable variables[], int count, const char *name)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(variables[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

void set_variable(Variable variables[], int *count, const char *name, const char *value)
{
    int index = find_variable(variables, *count, name);
    if (index == -1)
    {
        index = (*count)++;
    }
    strcpy(variables[index].name, name);
    strcpy(variables[index].value, value);
}

const char *get_variable(Variable variables[], int count, const char *name)
{
    int index = find_variable(variables, count, name);
    if (index != -1)
    {
        return variables[index].value;
    }
    return NULL;
}
