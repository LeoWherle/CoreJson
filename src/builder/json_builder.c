/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_builder
*/

// reallocarray, malloc
#include <stdlib.h>
// memcpy, strlen
#include <string.h>
// DERR
#include <stdio.h>
#include "corejson_internal.h"

char *key_strdup(const char *s)
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

int value_strdup(char *dest, const char *src)
{
    uint32_t i = 0;

    for (; src[i] != '\0'; i++) {
        dest[i] = src[i];
        if (i >= VALUE_LEN_MAX) {
            FLOG(stderr, "String value too long MAX: %d\n", VALUE_LEN_MAX);
            return 1;
        }
    }
    dest[i] = '\0';
    return 0;
}

int jsn_object_add_data(
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

int jsn_array_add_data(json_array_t *array, json_value_t *element)
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

json_value_t *jsn_null_create(void)
{
    json_value_t *value = NULL;

    value = malloc(sizeof(json_value_t));
    if (value == NULL)
        return NULL;
    value->type = JSON_NULL;
    return value;
}
