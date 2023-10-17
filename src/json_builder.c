// reallocarray
#include <stdlib.h>
// memcpy, strdup
#include <string.h>
// perror
#include <stdio.h>
#include "corejson.h"

int object_data_add(JSONObject *object, JSONValue *property, char *key_buffer)
{
    object->values =
        reallocarray(object->values, (object->size + 1), sizeof(JSONValue));
    if (object->values == NULL) {
        perror("reallocarray");
        return 1;
    }
    memcpy(&object->values[object->size], property, sizeof(JSONValue));
    object->keys =
        reallocarray(object->keys, (object->size + 1), sizeof(char *));
    if (object->keys == NULL) {
        perror("reallocarray");
        return 1;
    }
    object->keys[object->size] = strdup(key_buffer);
    object->size++;
    return 0;
}

int array_data_add(JSONArray *array, JSONValue *element)
{
    array->elements =
        reallocarray(array->elements, (array->size + 1), sizeof(JSONValue));
    if (array->elements == NULL) {
        perror("reallocarray");
        return 1;
    }
    memcpy(&array->elements[array->size], element, sizeof(JSONValue));
    array->size++;
    return 0;
}
