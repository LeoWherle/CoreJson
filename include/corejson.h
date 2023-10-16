/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** corejson
*/

#ifndef COREJSON_H_
#define COREJSON_H_

#include <stdbool.h>
#include <stdint.h>
#include "corejson_lexer.h"

typedef struct JSONValue JSONValue;
typedef struct JSONObject JSONObject;
typedef struct JSONArray JSONArray;

typedef enum {
    JSON_STRING,
    JSON_NUMBER,
    JSON_TRUE,
    JSON_FALSE,
    JSON_NULL,
    JSON_OBJECT,
    JSON_ARRAY,
} JSONValueType;

struct JSONValue {
    JSONValueType type;
    union {
        char string_value[VALUE_MAX_LEN + 1];
        double number_value;
        JSONObject *object_value;
        JSONArray *array_value;
        bool bool_value;
    };
};

struct JSONObject {
    JSONValue *values;
    char **keys;
    size_t size;
};

struct JSONArray {
    JSONValue *elements;
    size_t size;
};


/** PARSING **/
JSONValue *json_parse(const char *json);

JSONValue *parse_value(const char **json);

/** PRINT **/
void json_print(JSONValue *jsonValue, bool format, int fd);

void json_print_value(JSONValue *jsonValue, uint32_t, bool format, int fd);

/** DESTRUCTORS **/
void json_free(JSONValue *jsonValue);

void json_object_free(JSONObject *object);
void json_array_free(JSONArray *array);
void json_value_free(JSONValue *jsonValue);

#endif /* !COREJSON_H_ */
