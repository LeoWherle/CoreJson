/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_lexer_tokens
*/

#include "corejson_internal.h"

void jsn_token_end(UNUSED const char **json, token_t *token)
{
    token->type = TOKEN_END;
}

void jsn_token_left_brace(const char **json, token_t *token)
{
    parse_char(json, token, TOKEN_LEFT_BRACE);
}

void jsn_token_right_brace(const char **json, token_t *token)
{
    parse_char(json, token, TOKEN_RIGHT_BRACE);
}

void jsn_token_left_bracket(const char **json, token_t *token)
{
    parse_char(json, token, TOKEN_LEFT_BRACKET);
}

void jsn_token_right_bracket(const char **json, token_t *token)
{
    parse_char(json, token, TOKEN_RIGHT_BRACKET);
}

void jsn_token_null(const char **json, token_t *token)
{
    parse_string_spec(json, token, TOKEN_NULL, "null");
}
