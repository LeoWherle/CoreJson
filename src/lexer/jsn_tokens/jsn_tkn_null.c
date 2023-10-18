/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** jsn_tkn_comma
*/

#include "corejson_internal.h"

void jsn_token_null(const char **json, token_t *token)
{
    parse_string_spec(json, token, TOKEN_NULL, NULL_STR);
}
