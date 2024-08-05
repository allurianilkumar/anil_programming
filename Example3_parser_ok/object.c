#include "object.h"

// Function to create a new dynamic object
DynamicObject *create_object(const char *name)
{
    DynamicObject *obj = (DynamicObject *)malloc(sizeof(DynamicObject));
    if (!obj)
    {
        perror("Failed to create object");
        exit(EXIT_FAILURE);
    }

    obj->name = strdup(name);
    obj->id = NULL;
    obj->attributes = NULL;

    return obj;
}

// Function to destroy a dynamic object
void destroy_object(DynamicObject *obj)
{
    if (obj)
    {
        free(obj->name);
        free(obj->id);
        free(obj->attributes);
        free(obj);
    }
}

// Function to set an attribute of a dynamic object
void set_attribute(DynamicObject *obj, const char *key, const char *value)
{
    if (!obj || !key || !value)
        return;

    // For simplicity, we'll store attributes as "key=value" in a single string
    size_t key_len = strlen(key);
    size_t value_len = strlen(value);
    size_t new_size = key_len + value_len + 2; // Key + "=" + Value + Null terminator

    char *new_attr = (char *)malloc(new_size);
    if (!new_attr)
    {
        perror("Failed to set attribute");
        exit(EXIT_FAILURE);
    }

    snprintf(new_attr, new_size, "%s=%s", key, value);

    if (obj->attributes)
    {
        free(obj->attributes); // Free old attributes
    }

    obj->attributes = new_attr;
}

// Function to get an attribute value of a dynamic object
char *get_attribute(const DynamicObject *obj, const char *key)
{
    if (!obj || !key || !obj->attributes)
        return NULL;

    size_t key_len = strlen(key);
    char *attr = strstr(obj->attributes, key);

    if (attr && (attr[key_len] == '='))
    {
        return strdup(attr + key_len + 1); // Return value part after '='
    }

    return NULL;
}
