/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_free
*/

#include <stdlib.h>
#include "corejson.h"

void json_array_free(json_array_t *array)
{
    for (uint32_t i = 0; i < array->size; i++) {
        json_value_free(&array->elements[i]);
    }
    free(array->elements);
    free(array);
}

void json_object_free(json_object_t *object)
{
    for (uint32_t i = 0; i < object->size; i++) {
        json_value_free(&object->values[i]);
        free(object->keys[i]);
    }
    free(object->values);
    free(object->keys);
    free(object);
}

void json_value_free(json_value_t *jsonValue)
{
    if (jsonValue == NULL) {
        return;
    }
    switch (jsonValue->type) {
        case JSON_ARRAY:
            json_array_free(jsonValue->array_value);
            break;
        case JSON_OBJECT:
            json_object_free(jsonValue->object_value);
            break;
        case JSON_NUMBER:
        case JSON_FALSE:
        case JSON_TRUE:
        case JSON_STRING:
        case JSON_NULL:
        default:
            break;
    }
}

void json_free(json_value_t *jsonValue)
{
    json_value_free(jsonValue);
    free(jsonValue);
}