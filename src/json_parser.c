#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corejson.h"
#include "corejson_internal.h"

parse_func_t parsefunc_table[] = {
    [TOKEN_STRING] = jns_parse_string,
    [TOKEN_NUMBER] = jns_parse_number,
    [TOKEN_TRUE] = jns_parse_true,
    [TOKEN_FALSE] = jns_parse_false,
    [TOKEN_NULL] = jns_parse_null,
    [TOKEN_LEFT_BRACE] = jns_parse_object,
    [TOKEN_LEFT_BRACKET] = jns_parse_array,
};

int jns_parse_string(JSONValue *value, token_t *token, UNUSED const char **json)
{
    value->type = JSON_STRING;
    strncpy(value->string_value, token->value, sizeof(value->string_value));
    return 0;
}

int jns_parse_number(JSONValue *value, token_t *token, UNUSED const char **json)
{
    value->type = JSON_NUMBER;
    value->number_value = atof(token->value);
    return 0;
}

int jns_parse_true(
    JSONValue *value, UNUSED token_t *token, UNUSED const char **json)
{
    value->type = JSON_TRUE;
    value->bool_value = true;
    return 0;
}

int jns_parse_false(
    JSONValue *value, UNUSED token_t *token, UNUSED const char **json)
{
    value->type = JSON_FALSE;
    value->bool_value = false;
    return 0;
}

int jns_parse_null(
    JSONValue *value, UNUSED token_t *token, UNUSED const char **json)
{
    value->type = JSON_NULL;
    return 0;
}

int jns_parse_object(JSONValue *value, UNUSED token_t *token, const char **json)
{
    value->type = JSON_OBJECT;
    value = parse_object(json, value);
    if (value->object_value == NULL) {
        return 1;
    }
    return 0;
}

int jns_parse_array(JSONValue *value, UNUSED token_t *token, const char **json)
{
    value->type = JSON_ARRAY;
    value = parse_array(json, value);
    if (value->array_value == NULL) {
        return 1;
    }
    return 0;
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
    if (parsefunc_table[token.type](value, &token, json) != 0) {
        free(value);
        return NULL;
    }
    return value;
}


JSONValue *json_parse(const char *json)
{
    JSONValue *value = NULL;

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
