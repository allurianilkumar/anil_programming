#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for the dynamic object
typedef struct
{
    char *name;
    char *id;
    char *attributes; // Store attributes as a key-value pair string
} DynamicObject;

// Function prototypes
DynamicObject *create_object(const char *name);
void destroy_object(DynamicObject *obj);
void set_attribute(DynamicObject *obj, const char *key, const char *value);
char *get_attribute(const DynamicObject *obj, const char *key);

#endif // OBJECT_H
