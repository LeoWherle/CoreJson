/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_parse_array
*/

#include "corejson_internal.h"

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
