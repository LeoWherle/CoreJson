/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_parse_array
*/

#include "corejson_internal.h"

int jsn_tkn_parse_null(
    json_value_t *value, UNUSED token_t *token, UNUSED const char **json)
{
    value->type = JSON_NULL;
    return 0;
}
