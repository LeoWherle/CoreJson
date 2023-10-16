/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** corejson
*/

#ifndef COREJSON_H_
    #define COREJSON_H_

#include <stdint.h>
#include <stdbool.h>
#include "corejson_lexer.h"

typedef struct JSONValue JSONValue;
typedef struct JSONObject JSONObject;
typedef struct JSONArray JSONArray;

typedef enum {
    JSON_STRING,
    JSON_NUMBER,
    JSON_OBJECT,
    JSON_ARRAY,
    JSON_TRUE,
    JSON_FALSE,
    JSON_NULL
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
    JSONValue *properties;
    char **keys;
    size_t size;
};


struct JSONArray {
    JSONValue *elements;
    size_t size;
};

#define parse_json(json) parse_value(&(json))

JSONValue *parse_value(const char **json);

void print_json(JSONValue *jsonValue, uint32_t depth);

void json_free(JSONValue *jsonValue);


#endif /* !COREJSON_H_ */
