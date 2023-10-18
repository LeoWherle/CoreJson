/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_parser
*/

#include <stdio.h>
#include <stdlib.h>
#include "corejson.h"
#include "corejson_internal.h"

static parse_func_t parsefunc_table[] = {
    [TOKEN_STRING] = jsn_tkn_parse_string,
    [TOKEN_NUMBER] = jsn_tkn_parse_number,
    [TOKEN_TRUE] = jsn_tkn_parse_true,
    [TOKEN_FALSE] = jsn_tkn_parse_false,
    [TOKEN_NULL] = jsn_tkn_parse_null,
    [TOKEN_LEFT_BRACE] = jsn_tkn_parse_object,
    [TOKEN_LEFT_BRACKET] = jsn_tkn_parse_array,
};

json_value_t *jsn_parse_value(const char **json)
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

json_value_t *jsn_parse(const char *json)
{
    json_value_t *value = NULL;

    value = jsn_parse_value(&json);
    if (value == NULL) {
        return NULL;
    }
    if (value->type != JSON_OBJECT) {
        jsn_free(value);
        return NULL;
    }
    return value;
}
