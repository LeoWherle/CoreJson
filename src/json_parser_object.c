// perror, fprintf
#include <stdio.h>
// malloc, free
#include <stdlib.h>
// memcpy
#include <string.h>
#include "corejson.h"

static int _init_object_data(JSONValue *value, JSONObject **object)
{
    *object = malloc(sizeof(JSONObject));
    if (*object == NULL) {
        perror("malloc");
        free(*object);
        return 1;
    } else {
        (*object)->size = 0;
        (*object)->values = NULL;
        (*object)->keys = NULL;
        value->type = JSON_OBJECT;
        value->object_value = *object;
        return 0;
    }
}

static int _get_key(JSONValue *value, char *key_buffer, const char **json)
{
    token_t token = {0};

    next_token(json, &token);
    if (token.type == TOKEN_RIGHT_BRACE) {
        return 1;
    } else if (token.type != TOKEN_STRING) {
        fprintf(stderr, "Expected string, got %s\n",
            token_type_get_string(token.type));
        value->type = JSON_NULL;
        return 2;
    } else {
        memcpy(key_buffer, token.value, VALUE_LEN_MAX);
        return 0;
    }
}

static int _get_value_and_set_data(
    JSONObject *object, JSONValue *value, char *key_buffer, const char **json)
{
    JSONValue *property = NULL;

    property = parse_value(json);
    if (property == NULL) {
        value->type = JSON_NULL;
        return 1;
    }
    if (object_data_add(object, property, key_buffer) != 0) {
        free(property);
        value->type = JSON_NULL;
        return 1;
    }
    free(property);
    return 0;
}

static int _object_has_no_data(JSONValue *value, const char **json)
{
    token_t token = {0};

    next_token(json, &token);
    if (token.type == TOKEN_COMMA) {
        return 0;
    } else if (token.type == TOKEN_RIGHT_BRACE) {
        return 1;
    } else {
        fprintf(stderr, "Expected %s or %s, got %s\n",
            token_type_get_string(TOKEN_COMMA),
            token_type_get_string(TOKEN_RIGHT_BRACE),
            token_type_get_string(token.type));
        value->type = JSON_NULL;
        return 1;
    }
}

static int _get_comma(JSONValue *value, const char **json)
{
    token_t token = {0};

    next_token(json, &token);
    if (token.type != TOKEN_COLON) {
        value->type = JSON_NULL;
        return 1;
    }
    return 0;
}

JSONValue *parse_object(const char **json, JSONValue *value)
{
    char key_buffer[VALUE_LEN_MAX + 1] = {0};
    JSONObject *object = NULL;

    if (_init_object_data(value, &object) != 0)
        return NULL;
    while (true) {
        if (_get_key(value, key_buffer, json) != 0)
            break;
        if (_get_comma(value, json) != 0)
            break;
        if (_get_value_and_set_data(object, value, key_buffer, json) != 0)
            break;
        if (_object_has_no_data(value, json) != 0)
            break;
    }
    if (value->type == JSON_NULL) {
        json_object_free(object);
    }
    return value;
}
