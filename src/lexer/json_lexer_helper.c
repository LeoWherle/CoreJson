/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_lexer_helper
*/

#include <stdint.h>
#include "corejson_internal.h"

static const char *token_type_string[] = {
    [TOKEN_STRING] = "TOKEN_STRING",
    [TOKEN_NUMBER] = "TOKEN_NUMBER",
    [TOKEN_TRUE] = "TOKEN_TRUE",
    [TOKEN_FALSE] = "TOKEN_FALSE",
    [TOKEN_NULL] = "TOKEN_NULL",
    [TOKEN_LEFT_BRACE] = "TOKEN_LEFT_BRACE",
    [TOKEN_RIGHT_BRACE] = "TOKEN_RIGHT_BRACE",
    [TOKEN_LEFT_BRACKET] = "TOKEN_LEFT_BRACKET",
    [TOKEN_RIGHT_BRACKET] = "TOKEN_RIGHT_BRACKET",
    [TOKEN_COLON] = "TOKEN_COLON",
    [TOKEN_COMMA] = "TOKEN_COMMA",
    [TOKEN_ERROR] = "TOKEN_ERROR",
    [TOKEN_END] = "TOKEN_END",
};

const char *token_type_get_string(token_type_e type)
{
    return token_type_string[type];
}

void jsn_token_string(const char **json, token_t *token)
{
    parse_string(json, token);
}

void jsn_token_number(const char **json, token_t *token)
{
    parse_number(json, token);
}

void jsn_token_true(const char **json, token_t *token)
{
    parse_string_spec(json, token, TOKEN_TRUE, "true");
}

void jsn_token_false(const char **json, token_t *token)
{
    parse_string_spec(json, token, TOKEN_FALSE, "false");
}
void jsn_token_colon(const char **json, token_t *token)
{
    parse_char(json, token, TOKEN_COLON);
}

void jsn_token_comma(const char **json, token_t *token)
{
    parse_char(json, token, TOKEN_COMMA);
}