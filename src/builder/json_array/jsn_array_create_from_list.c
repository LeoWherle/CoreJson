/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_create_advanced
*/

#include "builder/corejson_array.h"
#include "corejson_internal.h"

// must be null terminated
json_value_t *jsn_array_create_from_list_number(double *list, uint32_t size)
{
    json_value_t *value = NULL;
    uint32_t i = 0;

    if (list == NULL)
        return NULL;
    value = jsn_array_create();
    if (value == NULL)
        return NULL;
    for (i = 0; i < size; i++) {
        if (jsn_array_add_number(value, list[i])) {
            jsn_free(value);
            return NULL;
        }
    }
    return value;
}

// must be null terminated
json_value_t *jsn_array_create_from_list_string(
    const char **list, uint32_t size)
{
    json_value_t *value = NULL;
    uint32_t i = 0;

    if (list == NULL)
        return NULL;
    value = jsn_array_create();
    if (value == NULL)
        return NULL;
    for (i = 0; i < size; i++) {
        if (jsn_array_add_string(value, list[i])) {
            jsn_free(value);
            return NULL;
        }
    }
    return value;
}

// must be null terminated
json_value_t *jsn_array_create_from_list_bool(bool *list, uint32_t size)
{
    json_value_t *value = NULL;
    uint32_t i = 0;

    if (list == NULL)
        return NULL;
    value = jsn_array_create();
    if (value == NULL)
        return NULL;
    for (i = 0; i < size; i++) {
        if (jsn_array_add_bool(value, list[i])) {
            jsn_free(value);
            return NULL;
        }
    }
    return value;
}

// must be null terminated
json_value_t *jsn_array_create_from_list_object(
    json_object_t **list, uint32_t size)
{
    json_value_t *value = NULL;
    uint32_t i = 0;

    if (list == NULL)
        return NULL;
    value = jsn_array_create();
    if (value == NULL)
        return NULL;
    for (i = 0; i < size; i++) {
        if (jsn_array_add_object(value, list[i])) {
            jsn_free(value);
            return NULL;
        }
    }
    return value;
}

// must be null terminated
json_value_t *jsn_array_create_from_list_array(
    json_array_t **list, uint32_t size)
{
    json_value_t *value = NULL;
    uint32_t i = 0;

    if (list == NULL)
        return NULL;
    value = jsn_array_create();
    if (value == NULL)
        return NULL;
    for (i = 0; i < size; i++) {
        if (jsn_array_add_array(value, list[i])) {
            jsn_free(value);
            return NULL;
        }
    }
    return value;
}
