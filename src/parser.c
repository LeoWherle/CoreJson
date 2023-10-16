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
    next_token(json, &token);
    JSONValue *value = NULL;

    value = malloc(sizeof(JSONValue));
    if (value == NULL) {
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

// Function to parse a JSON object
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
    object->properties = NULL;
    object->keys = NULL;
    value->type = JSON_OBJECT;

    while (true) {
        next_token(json, &token);
        if (token.type == TOKEN_RIGHT_BRACE)
            break; // End of object

        if (token.type != TOKEN_STRING) {
            value->type = JSON_NULL; // Error in parsing
            break;
        }

        strncpy(key, token.value, sizeof(key));

        next_token(json, &token);
        if (token.type != TOKEN_COLON) {
            value->type = JSON_NULL; // Error in parsing
            break;
        }

        property = parse_value(json);
        if (property == NULL) {
            value->type = JSON_NULL;
            break;
        }

        // Expand the object's properties array
        object->properties =
            realloc(object->properties, (object->size + 1) * sizeof(JSONValue));
        if (object->properties == NULL) {
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
        memcpy(&object->properties[object->size], property, sizeof(JSONValue));
        free(property);
        object->keys[object->size] = strdup(key);
        object->size++;

        // Check for more properties or end of object
        next_token(json, &token);
        if (token.type == TOKEN_COMMA) {
            continue;
        } else if (token.type == TOKEN_RIGHT_BRACE) {
            break;
        } else {
            value->type = JSON_NULL; // Error in parsing
            break;
        }
    }

    if (value->type != JSON_NULL) {
        value->object_value = object;
    } else {
        // Clean up on error
        for (size_t i = 0; i < object->size; i++) {
            free(object->keys[i]);
        }
        free(object->keys);
        free(object->properties);
    }
    return value;
}

// Function to parse a JSON array
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
        next_token(json, &token);
        if (token.type == TOKEN_RIGHT_BRACKET)
            break; // End of array

        element = parse_value(json);
        if (element == NULL) {
            value->type = JSON_NULL;
            break;
        }

        // Expand the array's elements array
        array->elements =
            realloc(array->elements, (array->size + 1) * sizeof(JSONValue));
        if (array->elements == NULL) {
            value->type = JSON_NULL;
            free(element);
            break;
        }
        memcpy(element, &array->elements[array->size], sizeof(JSONValue));
        free(element);
        array->size++;

        // Check for more elements or end of array
        next_token(json, &token);
        if (token.type == TOKEN_COMMA) {
            continue;
        } else if (token.type == TOKEN_RIGHT_BRACKET) {
            break;
        } else {
            value->type = JSON_NULL; // Error in parsing
            break;
        }
    }

    if (value->type != JSON_NULL) {
        value->array_value = array;
    } else {
        // Clean up on error
        for (size_t i = 0; i < array->size; i++) {
            if (array->elements[i].type == JSON_STRING) {
                free(array->elements[i].string_value);
            }
        }
        free(array->elements);
    }

    return value;
}

// Function to recursively free JSON data
void free_json(JSONValue *jsonValue)
{
    if (jsonValue->type == JSON_OBJECT) {
        for (size_t i = 0; i < jsonValue->object_value->size; i++) {
            free_json(&jsonValue->object_value->properties[i]);
            free(jsonValue->object_value->keys[i]);
        }
        free(jsonValue->object_value->keys);
        free(jsonValue->object_value->properties);
    } else if (jsonValue->type == JSON_ARRAY) {
        for (size_t i = 0; i < jsonValue->array_value->size; i++) {
            free_json(&jsonValue->array_value->elements[i]);
        }
        free(jsonValue->array_value->elements);
    }
    free(jsonValue);
}

static void print_spaces(uint32_t depth)
{
    for (uint32_t i = 0; i < depth; i++) {
        printf("  ");
    }
}

void print_json(JSONValue *jsonValue, uint32_t depth)
{
    switch (jsonValue->type) {
        case JSON_ARRAY:
            printf("[\n");
            for (uint32_t i = 0; i < jsonValue->array_value->size; i++) {
                print_spaces(depth + 1);
                print_json(&jsonValue->array_value->elements[i], depth + 1);
            }
            printf("]\n");
            break;
        case JSON_OBJECT:
            print_spaces(depth);
            printf("{\n");
            for (uint32_t i = 0; i < jsonValue->object_value->size; i++) {
                print_spaces(depth + 1);
                printf("\"%s\": ", jsonValue->object_value->keys[i]);
                print_json(&jsonValue->object_value->properties[i], depth + 1);
            }
            print_spaces(depth);
            printf("}\n");
            break;
        case JSON_NUMBER: printf("%e\n", jsonValue->number_value); break;
        case JSON_FALSE:
        case JSON_TRUE:
            printf("%s\n", jsonValue->bool_value ? "true" : "false");
            break;
        case JSON_STRING: printf("%s\n", jsonValue->string_value); break;
        case JSON_NULL: printf("null"); break;

        default: break;
    }
}
void json_free(JSONValue *jsonValue)
{
    switch (jsonValue->type) {
        case JSON_ARRAY:
            for (uint32_t i = 0; i < jsonValue->array_value->size; i++) {
                json_free(&jsonValue->array_value->elements[i]);
            }
            free(jsonValue->array_value->elements);
            free(jsonValue->array_value);
            break;
        case JSON_OBJECT:
            for (uint32_t i = 0; i < jsonValue->object_value->size; i++) {
                json_free(&jsonValue->object_value->properties[i]);
                free(jsonValue->object_value->keys[i]);
            }
            free(jsonValue->object_value->properties);
            free(jsonValue->object_value->keys);
            free(jsonValue->object_value);
            break;
        case JSON_NUMBER:
        case JSON_FALSE:
        case JSON_TRUE:
        case JSON_STRING:
        case JSON_NULL: break;

        default: break;
    }
}
