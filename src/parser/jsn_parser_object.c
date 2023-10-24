/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_parser_object
*/

// malloc, free
#include <stdlib.h>
// memcpy
#include <string.h>
#include "corejson/internal.h"

static json_error_t init_object_data(
    json_value_t *value, json_object_t **object)
{
    *object = malloc(sizeof(json_object_t));
    if (*object == NULL) {
        DERR("malloc");
        free(*object);
        return JSN_ERROR;
    } else {
        (*object)->size = 0;
        (*object)->values = NULL;
        (*object)->keys = NULL;
        value->type = JSON_OBJECT;
        value->object_value = *object;
        return JSN_SUCCESS;
    }
}

static json_error_t get_key(
    json_value_t *value, char *key_buffer, const char **json)
{
    token_t token = {0};

    next_token(json, &token);
    if (token.type != TOKEN_STRING) {
        FLOG(stderr, "Expected string, got %s\n",
            token_type_get_string(token.type));
        value->type = JSON_NULL;
        return JSN_ERROR;
    } else {
        memcpy(key_buffer, token.value, VALUE_LEN_MAX);
        return JSN_SUCCESS;
    }
}

static json_error_t get_value_and_set_data(json_object_t *object,
    json_value_t *value, char *key_buffer, const char **json)
{
    json_value_t *property = NULL;

    property = jsn_parse_value(json);
    if (property == NULL) {
        value->type = JSON_NULL;
        return JSN_ERROR;
    }
    if (jsn_object_add_data(object, property, key_buffer) != 0) {
        free(property);
        value->type = JSON_NULL;
        return JSN_ERROR;
    }
    free(property);
    return JSN_SUCCESS;
}

static int object_has_no_data(json_value_t *value, const char **json)
{
    token_t token = {0};

    next_token(json, &token);
    if (token.type == TOKEN_COMMA) {
        return 0;
    } else if (token.type == TOKEN_RIGHT_BRACE) {
        return 1;
    } else {
        FLOG(stderr, "Expected %s or %s, got %s\n",
            token_type_get_string(TOKEN_COMMA),
            token_type_get_string(TOKEN_RIGHT_BRACE),
            token_type_get_string(token.type));
        value->type = JSON_NULL;
        return 1;
    }
}

static int get_comma(json_value_t *value, const char **json)
{
    token_t token = {0};

    next_token(json, &token);
    if (token.type != TOKEN_COLON) {
        value->type = JSON_NULL;
        return 1;
    }
    return JSN_SUCCESS;
}

json_value_t *jsn_parse_object(const char **json, json_value_t *value)
{
    char key_buffer[VALUE_LEN_MAX + 1] = {0};
    json_object_t *object = NULL;

    if (init_object_data(value, &object) != JSN_SUCCESS)
        return NULL;
    while (true) {
        if (get_key(value, key_buffer, json) != 0)
            break;
        if (get_comma(value, json) != 0)
            break;
        if (get_value_and_set_data(object, value, key_buffer, json) != 0)
            break;
        if (object_has_no_data(value, json) != 0)
            break;
    }
    if (value->type == JSON_NULL) {
        jsn_object_free(object);
        return NULL;
    }
    return value;
}
