/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** jsn_tkn_comma
*/

#include "corejson_internal.h"

void jsn_token_string(const char **json, token_t *token)
{
    parse_string(json, token);
}