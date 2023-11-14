/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_parse_array
*/

#include "corejson/internal.h"

json_error_t jsn_tkn_parse_true(
    json_value_t *value, UNUSED token_t *token, UNUSED const char **json)
{
    value->type = JSON_BOOL;
    value->bool_val = true;
    return JSN_SUCCESS;
}

json_error_t jsn_tkn_parse_false(
    json_value_t *value, UNUSED token_t *token, UNUSED const char **json)
{
    value->type = JSON_BOOL;
    value->bool_val = false;
    return JSN_SUCCESS;
}
