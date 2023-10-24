/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_create
*/

#include <stdlib.h>
#include "corejson_internal.h"

json_value_t *jsn_bool_create(bool bool_value)
{
    json_value_t *value = NULL;

    value = malloc(sizeof(json_value_t));
    if (value == NULL)
        return NULL;
    value->type = JSON_BOOL;
    value->bool_value = bool_value;
    return value;
}

json_value_t *jsn_number_create(double number_value)
{
    json_value_t *value = NULL;

    value = malloc(sizeof(json_value_t));
    if (value == NULL)
        return NULL;
    value->type = JSON_NUMBER;
    value->number_value = number_value;
    return value;
}

json_value_t *jsn_string_create(const char *string)
{
    json_value_t *value = NULL;

    if (string == NULL)
        return NULL;
    value = malloc(sizeof(json_value_t));
    if (value == NULL)
        return NULL;
    value->type = JSON_STRING;
    if (value_strdup(value->string_value, string)) {
        free(value);
        return NULL;
    }
    return value;
}

json_value_t *jsn_array_create(void)
{
    json_value_t *value = NULL;

    value = malloc(sizeof(json_value_t));
    if (value == NULL)
        return NULL;
    value->type = JSON_ARRAY;
    value->array_value = malloc(sizeof(json_array_t));
    if (value->array_value == NULL) {
        free(value);
        return NULL;
    }
    value->array_value->size = 0;
    value->array_value->elements = NULL;
    return value;
}

json_value_t *jsn_object_create(void)
{
    json_value_t *value = NULL;

    value = malloc(sizeof(json_value_t));
    if (value == NULL)
        return NULL;
    value->type = JSON_OBJECT;
    value->object_value = malloc(sizeof(json_object_t));
    if (value->object_value == NULL) {
        free(value);
        return NULL;
    }
    value->object_value->size = 0;
    value->object_value->values = NULL;
    value->object_value->keys = NULL;
    return value;
}
