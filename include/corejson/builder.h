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

/** Array add value **/
json_error_t jsn_array_add_null(json_value_t *array);
json_error_t jsn_array_add_number(json_value_t *array, double number);
json_error_t jsn_array_add_string(json_value_t *array, const char *string);
json_error_t jsn_array_add_bool(json_value_t *array, bool bool_value);
json_error_t jsn_array_add_object(json_value_t *array, json_object_t *object);
json_error_t jsn_array_add_array(
    json_value_t *array, json_array_t *array_value);

/** Object add value **/
json_error_t jsn_object_add_null(
    json_value_t *value, const char *key);
json_error_t jsn_object_add_number(
    json_value_t *array, const char *key, double number);
json_error_t jsn_object_add_string(
    json_value_t *array, const char *key, const char *string);
json_error_t jsn_object_add_bool(
    json_value_t *array, const char *key, bool bool_value);
json_error_t jsn_object_add_object(
    json_value_t *array, const char *key, json_object_t *object);
json_error_t jsn_object_add_array(
    json_value_t *array, const char *key, json_array_t *array_value);

/** Create from list **/
json_value_t *jsn_array_create_from_list_number(double *list, uint32_t size);
json_value_t *jsn_array_create_from_list_string(
    const char **list, uint32_t size);
json_value_t *jsn_array_create_from_list_bool(bool *list, uint32_t size);
json_value_t *jsn_array_create_from_list_object(
    json_object_t **list, uint32_t size);
json_value_t *jsn_array_create_from_list_array(
    json_array_t **list, uint32_t size);

/** Duplicate **/
json_value_t *jsn_dup(json_value_t *dst, const json_value_t *src);
#endif /* !COREJSON_ARRAY_H_ */
