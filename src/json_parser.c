#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corejson.h"


JSONValue *json_parse(const char *json)
{
    return parse_value(&json);
}

JSONValue *parse_value(const char **json)
{
    token_t token = {0};
    JSONValue *value = NULL;

    next_token(json, &token);
    value = malloc(sizeof(JSONValue));
    if (value == NULL) {
        perror("malloc");
        return NULL;
    }
    switch (token.type) {
        case TOKEN_STRING:
            value->type = JSON_STRING;
            strncpy(
                value->string_value, token.value, sizeof(value->string_value));
            break;
        case TOKEN_NUMBER:
            value->type = JSON_NUMBER;
            value->number_value = atof(token.value);
            break;
        case TOKEN_TRUE:
            value->type = JSON_TRUE;
            value->bool_value = true;
            break;
        case TOKEN_FALSE:
            value->type = JSON_FALSE;
            value->bool_value = false;
            break;
        case TOKEN_NULL: value->type = JSON_NULL; break;
        case TOKEN_LEFT_BRACE:
            free(value);
            value = parse_object(json);
            break;
        case TOKEN_LEFT_BRACKET:
            free(value);
            value = parse_array(json);
            break;
        default:
            free(value);
            value = NULL;
            break;
    }
    return value;
}

JSONValue *parse_array(const char **json)
{
    JSONValue *value = NULL;
    JSONArray *array = NULL;
    JSONValue *element = NULL;
    token_t token = {0};

    value = malloc(sizeof(JSONValue));
    array = malloc(sizeof(JSONArray));
    if (value == NULL || array == NULL) {
        free(value);
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
