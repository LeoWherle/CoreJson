/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_parser_array
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corejson.h"

static int init_object_data(json_value_t *value, json_array_t **array)
{
    *array = malloc(sizeof(json_array_t));
    if (*array == NULL) {
        DERR("malloc");
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

static int get_value_and_set_data(
    const char **json, json_value_t *value, json_array_t *array)
{
    json_value_t *element = NULL;

    element = parse_value(json);
    if (element == NULL) {
        json_value_free(element);
        value->type = JSON_NULL;
        return 1;
    }
    if (array_data_add(array, element) != 0) {
        json_free(element);
        value->type = JSON_NULL;
        return 1;
    }
    free(element);
    return 0;
}

json_value_t *parse_array(const char **json, json_value_t *value)
{
    json_array_t *array = NULL;

    if (init_object_data(value, &array) != 0) {
        return NULL;
    }
    while (true) {
        if (get_value_and_set_data(json, value, array) != 0)
            break;
        if (array_has_no_data(value, json) != 0)
            break;
    }
    if (value->type == JSON_NULL) {
        json_array_free(array);
        return NULL;
    }
    return value;
}
