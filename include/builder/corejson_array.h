/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** corejson_array
*/

#ifndef COREJSON_ARRAY_H_
// clang-format off
    #define COREJSON_ARRAY_H_

    #include "corejson.h"
// clang-format on

bool jsn_array_add_null(json_value_t *array);
bool jsn_array_add_number(json_value_t *array, double number);
bool jsn_array_add_string(json_value_t *array, const char *string);
bool jsn_array_add_bool(json_value_t *array, bool bool_value);
bool jsn_array_add_object(json_value_t *array, json_object_t *object);
bool jsn_array_add_array(json_value_t *array, json_array_t *array_value);

bool jsn_object_add_number(
    json_value_t *array, const char *key, double number);
bool jsn_object_add_string(
    json_value_t *array, const char *key, const char *string);
bool jsn_object_add_bool(
    json_value_t *array, const char *key, bool bool_value);
bool jsn_object_add_object(
    json_value_t *array, const char *key, json_object_t *object);
bool jsn_object_add_array(
    json_value_t *array, const char *key, json_array_t *array_value);

json_value_t *jsn_array_create_from_list_number(double *list, uint32_t size);
json_value_t *jsn_array_create_from_list_string(
    const char **list, uint32_t size);
json_value_t *jsn_array_create_from_list_bool(bool *list, uint32_t size);
json_value_t *jsn_array_create_from_list_object(
    json_object_t **list, uint32_t size);
json_value_t *jsn_array_create_from_list_array(
    json_array_t **list, uint32_t size);

#endif /* !COREJSON_ARRAY_H_ */
