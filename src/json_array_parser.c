#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corejson.h"

static int _init_object_data(JSONValue *value, JSONArray **array)
{
    *array = malloc(sizeof(JSONArray));
    if (*array == NULL) {
        perror("malloc");
        free(*array);
        return 1;
    } else {
        (*array)->size = 0;
        (*array)->elements = NULL;
        value->type = JSON_ARRAY;
        value->array_value = *array;
        return 0;
    }
}

static int _array_has_no_data(JSONValue *value, const char **json)
{
    token_t token = {0};

    next_token(json, &token);
    if (token.type == TOKEN_COMMA) {
        return 0;
    } else if (token.type == TOKEN_RIGHT_BRACKET) {
        return 1;
    } else {
        fprintf(stderr, "Expected %s or %s, got %s\n",
            token_type_get_string(TOKEN_COMMA),
            token_type_get_string(TOKEN_RIGHT_BRACKET),
            token_type_get_string(token.type));
        value->type = JSON_NULL;
        return 1;
    }
}

int _get_value_and_set_data(
    const char **json, JSONValue *value, JSONArray *array)
{
    JSONValue *element = NULL;

    element = parse_value(json);
    if (element == NULL) {
        value->type = JSON_NULL;
        return 1;
    }
    array->elements =
        reallocarray(array->elements, (array->size + 1), sizeof(JSONValue));
    if (array->elements == NULL) {
        value->type = JSON_NULL;
        perror("realloc");
        free(element);
        return 1;
    }
    memcpy(&array->elements[array->size], element, sizeof(JSONValue));
    free(element);
    array->size++;
    return 0;
}

JSONValue *parse_array(const char **json, JSONValue *value)
{
    JSONArray *array = NULL;

    if (_init_object_data(value, &array) != 0) {
        return NULL;
    }
    while (true) {
        if (_get_value_and_set_data(json, value, array) != 0)
            break;
        if (_array_has_no_data(value, json) != 0)
            break;
    }

    if (value->type == JSON_NULL) {
        json_array_free(array);
    }
    return value;
}

/*
JSONValue *parse_array(const char **json, JSONValue *value)
{
    JSONArray *array = NULL;
    JSONValue *element = NULL;
    token_t token = {0};

    array = malloc(sizeof(JSONArray));
    if (array == NULL) {
        free(array);
        return NULL;
    }

    array->size = 0;
    array->elements = NULL;
    value->type = JSON_ARRAY;
    while (true) {
        element = parse_value(json);
        if (element == NULL) {
            value->type = JSON_NULL;
            break;
        }

        array->elements =
            reallocarray(array->elements, (array->size + 1), sizeof(JSONValue));
        if (array->elements == NULL) {
            value->type = JSON_NULL;
            perror("realloc");
            free(element);
            break;
        }
        memcpy(&array->elements[array->size], element, sizeof(JSONValue));
        free(element);
        array->size++;

        next_token(json, &token);
        if (token.type == TOKEN_COMMA) {
            continue;
        } else if (token.type == TOKEN_RIGHT_BRACKET) {
            break;
        } else {
            value->type = JSON_NULL;
            break;
        }
    }

    if (value->type != JSON_NULL) {
        value->array_value = array;
    } else {
        json_array_free(array);
    }
    return value;
}
*/