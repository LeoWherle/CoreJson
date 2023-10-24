/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_create_advanced
*/

#include <stdlib.h>
#include <string.h>
#include "corejson/internal.h"
#include "corejson.h"

static json_error_t jsn_array_add_new(json_array_t *array)
{
    array->elements = reallocarray(
        array->elements, sizeof(json_value_t), (array->size + 1));
    if (array->elements == NULL) {
        return JSN_ERROR;
    }
    memset(&array->elements[array->size], 0, sizeof(json_value_t));
    return JSN_SUCCESS;
}

json_error_t jsn_array_add_number(json_value_t *value, double number)
{
    json_array_t *array = NULL;

    if (value == NULL || value->type != JSON_ARRAY) {
        return JSN_ERROR;
    }
    array = value->array_value;
    if (array == NULL) {
        return JSN_ERROR;
    }
    if (jsn_array_add_new(array)) {
        return JSN_ERROR;
    }
    array->elements[array->size].type = JSON_NUMBER;
    array->elements[array->size].number_value = number;
    array->size++;
    return JSN_SUCCESS;
}

json_error_t jsn_array_add_string(json_value_t *value, const char *string)
{
    json_array_t *array = NULL;

    if (value == NULL || value->type != JSON_ARRAY) {
        return JSN_ERROR;
    }
    array = value->array_value;
    if (array == NULL) {
        return JSN_ERROR;
    }
    if (jsn_array_add_new(array)) {
        return JSN_ERROR;
    }
    array->elements[array->size].type = JSON_STRING;
    if (value_strdup(array->elements[array->size].string_value, string) != 0) {
        return JSN_ERROR;
    }
    array->size++;
    return JSN_SUCCESS;
}

json_error_t jsn_array_add_bool(json_value_t *value, bool bool_value)
{
    json_array_t *array = NULL;

    if (value == NULL || value->type != JSON_ARRAY) {
        return JSN_ERROR;
    }
    array = value->array_value;
    if (array == NULL) {
        return JSN_ERROR;
    }
    if (jsn_array_add_new(array)) {
        return JSN_ERROR;
    }
    array->elements[array->size].type = JSON_BOOL;
    array->elements[array->size].bool_value = bool_value;
    array->size++;
    return JSN_SUCCESS;
}

json_error_t jsn_array_add_object(json_value_t *value, json_object_t *object)
{
    json_array_t *array = NULL;

    if (value == NULL || value->type != JSON_ARRAY) {
        return JSN_ERROR;
    }
    array = value->array_value;
    if (array == NULL) {
        return JSN_ERROR;
    }
    if (jsn_array_add_new(array) == JSN_ERROR) {
        return JSN_ERROR;
    }
    array->elements[array->size].type = JSON_OBJECT;
    array->elements[array->size].object_value = object;
    array->size++;
    return JSN_SUCCESS;
}

json_error_t jsn_array_add_array(json_value_t *value, json_array_t *array_value)
{
    json_array_t *array = NULL;

    if (value == NULL || value->type != JSON_ARRAY) {
        return JSN_ERROR;
    }
    array = value->array_value;
    if (array == NULL) {
        return JSN_ERROR;
    }
    if (jsn_array_add_new(array) == JSN_ERROR) {
        return JSN_ERROR;
    }
    array->elements[array->size].type = JSON_ARRAY;
    array->elements[array->size].array_value = array_value;
    array->size++;
    return JSN_SUCCESS;
}
