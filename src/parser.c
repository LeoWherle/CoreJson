#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corejson.h"

static JSONValue *parse_object(const char **json);
static JSONValue *parse_array(const char **json);

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

static JSONValue *parse_object(const char **json)
{
    char key[VALUE_MAX_LEN] = {0};
    JSONValue *value = NULL;
    JSONObject *object = NULL;
    JSONValue *property = NULL;
    token_t token = {0};

    value = malloc(sizeof(JSONValue));
    object = malloc(sizeof(JSONObject));
    if (value == NULL || object == NULL) {
        free(value);
        free(object);
    }
    object->size = 0;
    object->values = NULL;
    object->keys = NULL;
    value->type = JSON_OBJECT;

    while (true) {
        next_token(json, &token);
        if (token.type == TOKEN_RIGHT_BRACE)
            break;

        if (token.type != TOKEN_STRING) {
            value->type = JSON_NULL;
            break;
        }

        strncpy(key, token.value, sizeof(key));

        next_token(json, &token);
        if (token.type != TOKEN_COLON) {
            value->type = JSON_NULL;
            break;
        }

        property = parse_value(json);
        if (property == NULL) {
            value->type = JSON_NULL;
            break;
        }

        object->values =
            realloc(object->values, (object->size + 1) * sizeof(JSONValue));
        if (object->values == NULL) {
            value->type = JSON_NULL;
            free(property);
            break;
        }
        object->keys =
            realloc(object->keys, (object->size + 1) * sizeof(char *));
        if (object->keys == NULL) {
            value->type = JSON_NULL;
            free(property);
            break;
        }
        memcpy(&object->values[object->size], property, sizeof(JSONValue));
        free(property);
        object->keys[object->size] = strdup(key);
        object->size++;

        next_token(json, &token);
        if (token.type == TOKEN_COMMA) {
            continue;
        } else if (token.type == TOKEN_RIGHT_BRACE) {
            break;
        } else {
            value->type = JSON_NULL;
            break;
        }
    }

    if (value->type != JSON_NULL) {
        value->object_value = object;
    } else {
        for (size_t i = 0; i < object->size; i++) {
            free(object->keys[i]);
        }
        free(object->keys);
        free(object->values);
    }
    return value;
}

static JSONValue *parse_array(const char **json)
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
        for (size_t i = 0; i < array->size; i++) {
            if (array->elements[i].type == JSON_STRING) {
                free(array->elements[i].string_value);
            }
        }
        free(array->elements);
    }
    return value;
}
