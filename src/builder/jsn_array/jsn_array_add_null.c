/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** jsn_array_constructor
*/

#include <stdlib.h>
#include "corejson/internal.h"

json_error_t jsn_array_add_null(json_value_t *value)
{
    json_array_t *array = NULL;

    if (value == NULL || value->type != JSON_ARRAY) {
        return JSN_ERROR;
    }
    array = value->arr_val;
    if (array == NULL) {
        return JSN_ERROR;
    }
    array->elem =
        reallocarray(array->elem, sizeof(json_value_t), (array->size + 1));
    if (array->elem == NULL) {
        return JSN_ERROR;
    }
    array->elem[array->size].type = JSON_NULL;
    array->size++;
    return JSN_SUCCESS;
}
