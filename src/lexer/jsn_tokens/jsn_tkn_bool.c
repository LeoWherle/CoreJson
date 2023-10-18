/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** jsn_tkn_bool
*/

#include "corejson_internal.h"

void jsn_token_false(const char **json, token_t *token)
{
    parse_string_spec(json, token, TOKEN_FALSE, FALSE_STR);
}

void jsn_token_true(const char **json, token_t *token)
{
    parse_string_spec(json, token, TOKEN_TRUE, TRUE_STR);
}
