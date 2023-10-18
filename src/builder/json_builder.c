/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_builder
*/

// reallocarray
#include <stdlib.h>
// memcpy, strdup
#include <string.h>
// DERR
#include <stdio.h>
#include "corejson_internal.h"

static char *key_strdup(const char *s)
{
    size_t len = 0;
    char *new = NULL;

    len = strlen(s) + 1;
    new = malloc(len);
    if (new != NULL) {
        new = (char *) memcpy(new, s, len);
        return new;
    }
    DERR("malloc");
    return new;
}

int jsn_object_data_add(
    json_object_t *object, json_value_t *property, const char *key_buffer)
{
    object->values =
        reallocarray(object->values, (object->size + 1), sizeof(json_value_t));
    if (object->values == NULL) {
        DERR("reallocarray");
        return 1;
    }
    memcpy(&object->values[object->size], property, sizeof(json_value_t));
    object->keys =
        reallocarray(object->keys, (object->size + 1), sizeof(char *));
    if (object->keys == NULL) {
        DERR("reallocarray");
        return 1;
    }
    object->keys[object->size] = key_strdup(key_buffer);
    if (object->keys[object->size] == NULL) {
        return 1;
    }
    object->size++;
    return 0;
}

int jsn_array_data_add(json_array_t *array, json_value_t *element)
{
    array->elements =
        reallocarray(array->elements, (array->size + 1), sizeof(json_value_t));
    if (array->elements == NULL) {
        DERR("reallocarray");
        return 1;
    }
    memcpy(&array->elements[array->size], element, sizeof(json_value_t));
    array->size++;
    return 0;
}
