/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** corejson
*/

#ifndef COREJSON_H_
    #define COREJSON_H_

    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include "corejson_lexer.h"

    #define NULL_STR "null"
    #define TRUE_STR "true"
    #define FALSE_STR "false"

typedef struct json_value_s json_value_t;
typedef struct json_object_s json_object_t;
typedef struct json_array_s json_array_t;

typedef enum {
    JSON_STRING,
    JSON_NUMBER,
    JSON_TRUE,
    JSON_FALSE,
    JSON_NULL,
    JSON_OBJECT,
    JSON_ARRAY
} json_value_type;

    #define IS_JSON_VALUE(t) (t >= JSON_STRING && t <= JSON_ARRAY)

struct json_value_s {
    json_value_type type;
    union {
        char string_value[VALUE_LEN_MAX + 1];
        double number_value;
        json_object_t *object_value;
        json_array_t *array_value;
        bool bool_value;
    };
};

struct json_object_s {
    json_value_t *values;
    char **keys;
    size_t size;
};

struct json_array_s {
    json_value_t *elements;
    size_t size;
};

/** PARSING **/
json_value_t *json_parse(const char *json);

json_value_t *parse_value(const char **json);
json_value_t *parse_object(const char **json, json_value_t *jsonValue);
json_value_t *parse_array(const char **json, json_value_t *jsonValue);

/** CONSTRUCTORS **/
int object_data_add(
    json_object_t *object, json_value_t *property, const char *key_buffer);
int array_data_add(json_array_t *array, json_value_t *element);

/** PRINT **/
void json_print(json_value_t *jsonValue, bool format, int fd);

void json_print_value(json_value_t *jsonValue, uint32_t, bool format, int fd);

/** DESTRUCTORS **/
void json_free(json_value_t *jsonValue);

void json_object_free(json_object_t *object);
void json_array_free(json_array_t *array);
void json_value_free(json_value_t *jsonValue);

#endif /* !COREJSON_H_ */
