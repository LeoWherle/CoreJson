/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_parse_array
*/

#include <string.h>
#include "corejson_internal.h"

int jsn_tkn_parse_string(
    json_value_t *value, token_t *token, UNUSED const char **json)
{
    value->type = JSON_STRING;
    memcpy(value->string_value, token->value, sizeof(value->string_value));
    return 0;
}
