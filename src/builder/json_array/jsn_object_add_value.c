/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_create_advanced
*/

#include <stdlib.h>
#include <string.h>
#include "builder/corejson_array.h"
#include "corejson_internal.h"

static bool jsn_object_add_new(json_object_t *object, const char *key)
{
    object->keys =
        reallocarray(object->keys, sizeof(char *), (object->size + 1));
    if (object->keys == NULL)
        return JSN_ERROR;
    object->keys[object->size] = NULL;
    object->values =
        reallocarray(object->values, sizeof(json_value_t), (object->size + 1));
    if (object->values == NULL) {
        return JSN_ERROR;
    }
    memset(&object->values[object->size], 0, sizeof(json_value_t));
    object->keys[object->size] = key_strdup(key);
    if (object->keys[object->size] == NULL) {
        return JSN_ERROR;
    }
    return JSN_SUCCESS;
}

bool jsn_object_add_number(json_value_t *value, const char *key, double number)
{
    json_object_t *object = NULL;

    if (value == NULL || value->object_value == NULL || key == NULL
        || value->type != JSON_OBJECT)
        return JSN_ERROR;
    object = value->object_value;
    if (jsn_object_add_new(object, key) == JSN_ERROR) {
        object->size++;
        return JSN_ERROR;
    }
    object->values[object->size].type = JSON_NUMBER;
    object->values[object->size].number_value = number;
    object->size++;
    return JSN_SUCCESS;
}

bool jsn_object_add_string(
    json_value_t *value, const char *key, const char *string)
{
    json_object_t *object = NULL;

    if (value == NULL || value->object_value == NULL || key == NULL
        || value->type != JSON_OBJECT || string == NULL)
        return JSN_ERROR;
    object = value->object_value;
    if (jsn_object_add_new(object, key) == JSN_ERROR) {
        object->size++;
        return JSN_ERROR;
    }
    object->values[object->size].type = JSON_STRING;
    if (value_strdup(object->values[object->size].string_value, string) != 0) {
        object->size++;
        return JSN_ERROR;
    }
    object->size++;
    return JSN_SUCCESS;
}

bool jsn_object_add_bool(json_value_t *value, const char *key, bool bool_value)
{
    json_object_t *object = NULL;

    if (value == NULL || value->object_value == NULL || key == NULL
        || value->type != JSON_OBJECT)
        return JSN_ERROR;
    object = value->object_value;
    if (jsn_object_add_new(object, key) == JSN_ERROR) {
        object->size++;
        return JSN_ERROR;
    }
    object->values[object->size].type = JSON_BOOL;
    object->values[object->size].bool_value = bool_value;
    object->size++;
    return JSN_SUCCESS;
}

// TODO add duplicate object_value
bool jsn_object_add_object(
    json_value_t *value, const char *key, json_object_t *object_value)
{
    json_object_t *object = NULL;

    if (value == NULL || value->object_value == NULL || key == NULL
        || value->type != JSON_OBJECT || object_value == NULL)
        return JSN_ERROR;
    object = value->object_value;
    if (jsn_object_add_new(object, key) == JSN_ERROR) {
        object->size++;
        return JSN_ERROR;
    }
    object->values[object->size].type = JSON_OBJECT;
    object->values[object->size].object_value = object_value;
    object->size++;
    return JSN_SUCCESS;
}

bool jsn_object_add_array(
    json_value_t *value, const char *key, json_array_t *array_value)
{
    json_object_t *object = NULL;

    if (value == NULL || value->object_value == NULL || key == NULL
        || value->type != JSON_OBJECT || array_value == NULL)
        return JSN_ERROR;
    object = value->object_value;
    if (jsn_object_add_new(object, key) == JSN_ERROR) {
        object->size++;
        return JSN_ERROR;
    }
    object->values[object->size].type = JSON_ARRAY;
    object->values[object->size].array_value = array_value;
    object->size++;
    return JSN_SUCCESS;
}
