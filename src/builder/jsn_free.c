/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_free
*/

#include <stdlib.h>
#include "corejson/internal.h"

static void jsn_array_values_free(json_array_t *array)
{
    uint32_t i = 0;

    if (array == NULL) {
        return;
    }
    for (; i < array->size; i++) {
        if (array->elem != NULL) {
            jsn_value_free(&array->elem[i]);
        }
    }
    free(array->elem);
    array->elem = NULL;
    array->size = 0;
}

void jsn_array_free(json_array_t *array)
{
    jsn_array_values_free(array);
    free(array);
}

static void jsn_object_values_free(json_object_t *object)
{
    uint32_t i = 0;

    if (object == NULL) {
        return;
    }
    for (; i < object->size; i++) {
        if (object->values != NULL) {
            jsn_value_free(&object->values[i]);
        }
        if (object->keys != NULL) {
            free(object->keys[i]);
        }
    }
    free(object->values);
    free(object->keys);
    object->keys = NULL;
    object->values = NULL;
    object->size = 0;
}

void jsn_object_free(json_object_t *object)
{
    jsn_object_values_free(object);
    free(object);
}

void jsn_value_free(json_value_t *jsonValue)
{
    if (jsonValue == NULL) {
        return;
    }
    switch (jsonValue->type) {
        case JSON_ARRAY:
            jsn_array_free(jsonValue->arr_val);
            break;
        case JSON_OBJECT:
            jsn_object_free(jsonValue->obj_val);
            break;
        case JSON_NUMBER:
        case JSON_BOOL:
        case JSON_STRING:
        case JSON_NULL:
        default:
            break;
    }
}

void jsn_free(json_value_t *jsonValue)
{
    jsn_value_free(jsonValue);
    free(jsonValue);
}
