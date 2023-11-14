/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_create
*/

#include <stdlib.h>
#include "corejson/internal.h"

json_value_t *jsn_bool_create(bool bool_value)
{
    json_value_t *value = NULL;

    value = malloc(sizeof(json_value_t));
    if (value == NULL)
        return NULL;
    value->type = JSON_BOOL;
    value->bool_val = bool_value;
    return value;
}

json_value_t *jsn_number_create(double number_value)
{
    json_value_t *value = NULL;

    value = malloc(sizeof(json_value_t));
    if (value == NULL)
        return NULL;
    value->type = JSON_NUMBER;
    value->nbr_val = number_value;
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
    if (value_strdup(value->str_val, string)) {
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
    value->arr_val = malloc(sizeof(json_array_t));
    if (value->arr_val == NULL) {
        free(value);
        return NULL;
    }
    value->arr_val->size = 0;
    value->arr_val->elem = NULL;
    return value;
}

json_value_t *jsn_object_create(void)
{
    json_value_t *value = NULL;

    value = malloc(sizeof(json_value_t));
    if (value == NULL)
        return NULL;
    value->type = JSON_OBJECT;
    value->obj_val = malloc(sizeof(json_object_t));
    if (value->obj_val == NULL) {
        free(value);
        return NULL;
    }
    value->obj_val->size = 0;
    value->obj_val->values = NULL;
    value->obj_val->keys = NULL;
    return value;
}
