/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_parser_array
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corejson/internal.h"

static json_error_t init_object_data(json_value_t *value, json_array_t **array)
{
    *array = malloc(sizeof(json_array_t));
    if (*array == NULL) {
        DERR("malloc");
        free(*array);
        return JSN_ERROR;
    } else {
        (*array)->size = 0;
        (*array)->elements = NULL;
        value->type = JSON_ARRAY;
        value->array_value = *array;
        return JSN_SUCCESS;
    }
}

static int array_has_no_data(json_value_t *value, const char **json)
{
    token_t token = {0};

    next_token(json, &token);
    if (token.type == TOKEN_COMMA) {
        return 0;
    } else if (token.type == TOKEN_RIGHT_BRACKET) {
        return 1;
    } else {
        FLOG(stderr, "Expected %s or %s, got %s\n",
            token_type_get_string(TOKEN_COMMA),
            token_type_get_string(TOKEN_RIGHT_BRACKET),
            token_type_get_string(token.type));
        value->type = JSON_NULL;
        return 1;
    }
}

static json_error_t get_value_and_set_data(
    const char **json, json_value_t *value, json_array_t *array)
{
    json_value_t *element = NULL;

    element = jsn_parse_value(json);
    if (element == NULL) {
        jsn_value_free(element);
        value->type = JSON_NULL;
        return JSN_ERROR;
    }
    if (jsn_array_add_data(array, element) != 0) {
        jsn_free(element);
        value->type = JSON_NULL;
        return JSN_ERROR;
    }
    free(element);
    return JSN_SUCCESS;
}

json_value_t *jsn_parse_array(const char **json, json_value_t *value)
{
    json_array_t *array = NULL;

    if (init_object_data(value, &array) != JSN_SUCCESS) {
        return NULL;
    }
    while (true) {
        if (get_value_and_set_data(json, value, array) != 0)
            break;
        if (array_has_no_data(value, json) != JSN_SUCCESS)
            break;
    }
    if (value->type == JSON_NULL) {
        jsn_array_free(array);
        return NULL;
    }
    return value;
}
