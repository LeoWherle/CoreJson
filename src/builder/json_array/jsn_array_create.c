/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** jsn_array_constructor
*/

#include <stdlib.h>
#include "corejson_internal.h"

bool jsn_array_add_null(json_value_t *value)
{
    json_array_t *array = NULL;

    if (value == NULL || value->type != JSON_ARRAY) {
        return JSN_ERROR;
    }
    array = value->array_value;
    if (array == NULL) {
        return JSN_ERROR;
    }
    array->elements =
        realloc(array->elements, sizeof(json_value_t) * (array->size + 1));
    if (array->elements == NULL) {
        return JSN_ERROR;
    }
    array->elements[array->size].type = JSON_NULL;
    array->size++;
    return JSN_SUCCESS;
}
