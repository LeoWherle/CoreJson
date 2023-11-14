/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** corejson_lexer_internal
*/

#ifndef COREJSON_INTERNAL_H_
// clang-format off
    #define COREJSON_INTERNAL_H_

    #include "corejson.h"
    #include "corejson/builder.h"
    #include "corejson/lexer.h"
// clang-format on

/** Printer handle **/
typedef void (*json_print_func_t)(
    json_value_t *val, uint32_t depth, uint32_t format, int fd);

/** Duplictation handle **/
typedef int (*jsn_dup_tble_t)(json_value_t *dst, json_value_t *src);

struct json_object_s {
    json_value_t *values;
    char **keys;
    size_t size;
};

struct json_array_s {
    json_value_t *elem;
    size_t size;
};

/** PRINTER **/
void jsn_object_print(
    json_value_t *value, uint32_t depth, uint32_t format, int fd);
void jsn_array_print(
    json_value_t *value, uint32_t depth, uint32_t format, int fd);
void jsn_number_print(
    json_value_t *value, uint32_t depth, uint32_t format, int fd);
void jsn_bool_print(
    json_value_t *value, uint32_t depth, uint32_t format, int fd);
void jsn_string_print(
    json_value_t *value, uint32_t depth, uint32_t format, int fd);
void jsn_null_print(
    json_value_t *value, uint32_t depth, uint32_t format, int fd);

void print_spaces(uint32_t depth, int fd, uint32_t format);
void jsn_value_print(
    json_value_t *jsonValue, uint32_t, uint32_t format, int fd);

/** Duplicate **/
json_error_t jsn_array_dup(json_value_t *dst, const json_value_t *src);
json_error_t jsn_object_dup(json_value_t *dst, const json_value_t *src);

/** FREE **/
void jsn_object_free(json_object_t *object);
void jsn_array_free(json_array_t *array);

/** HELPER **/
json_error_t value_strdup(char *dest, const char *src);
char *key_strdup(const char *s);
#endif /* !COREJSON_INTERNAL_H_ */
