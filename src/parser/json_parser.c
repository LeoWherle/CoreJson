/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_parser
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corejson.h"
#include "corejson_internal.h"

static parse_func_t parsefunc_table[] = {
    [TOKEN_STRING] = jns_parse_string,
    [TOKEN_NUMBER] = jns_parse_number,
    [TOKEN_TRUE] = jns_parse_true,
    [TOKEN_FALSE] = jns_parse_false,
    [TOKEN_NULL] = jns_parse_null,
    [TOKEN_LEFT_BRACE] = jns_parse_object,
    [TOKEN_LEFT_BRACKET] = jns_parse_array,
};

int jns_parse_string(
    json_value_t *value, token_t *token, UNUSED const char **json)
{
    value->type = JSON_STRING;
    memcpy(value->string_value, token->value, sizeof(value->string_value));
    return 0;
}

int jns_parse_number(
    json_value_t *value, token_t *token, UNUSED const char **json)
{
    value->type = JSON_NUMBER;
    value->number_value = atof(token->value);
    return 0;
}

int jns_parse_true(
    json_value_t *value, UNUSED token_t *token, UNUSED const char **json)
{
    value->type = JSON_TRUE;
    value->bool_value = true;
    return 0;
}

int jns_parse_false(
    json_value_t *value, UNUSED token_t *token, UNUSED const char **json)
{
    value->type = JSON_FALSE;
    value->bool_value = false;
    return 0;
}

int jns_parse_null(
    json_value_t *value, UNUSED token_t *token, UNUSED const char **json)
{
    value->type = JSON_NULL;
    return 0;
}

int jns_parse_object(
    json_value_t *value, UNUSED token_t *token, const char **json)
{
    value->type = JSON_OBJECT;
    value = parse_object(json, value);
    if (value == NULL) {
        FLOG(stderr, "Failed to parse array\n");
        return 1;
    }
    if (value->object_value == NULL) {
        FLOG(stderr, "Failed to parse array\n");
        return 1;
    }
    return 0;
}

int jns_parse_array(
    json_value_t *value, UNUSED token_t *token, const char **json)
{
    value->type = JSON_ARRAY;
    value = parse_array(json, value);
    if (value == NULL) {
        FLOG(stderr, "Failed to parse array\n");
        return 1;
    }
    if (value->array_value == NULL) {
        FLOG(stderr, "Failed to parse array\n");
        return 1;
    }
    return 0;
}

json_value_t *parse_value(const char **json)
{
    token_t token = {0};
    json_value_t *value = NULL;

    next_token(json, &token);
    value = malloc(sizeof(json_value_t));
    if (value == NULL) {
        DERR("malloc");
        return NULL;
    }
    if (!IS_TOKN_VAL(token.type)) {
        FLOG(stderr, "Expected a valid value, got %s\n",
            token_type_get_string(token.type));
        free(value);
        return NULL;
    }
    if (parsefunc_table[token.type](value, &token, json) != 0) {
        free(value);
        return NULL;
    }
    return value;
}

json_value_t *json_parse(const char *json)
{
    json_value_t *value = NULL;

    value = parse_value(&json);
    if (value == NULL) {
        return NULL;
    }
    if (value->type != JSON_OBJECT) {
        json_free(value);
        return NULL;
    }
    return value;
}
