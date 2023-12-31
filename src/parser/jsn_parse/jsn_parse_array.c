/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_parse_array
*/

#include "corejson/internal.h"

json_error_t jsn_tkn_parse_array(
    json_value_t *value, UNUSED token_t *token, const char **json)
{
    value->type = JSON_ARRAY;
    value = jsn_parse_array(json, value);
    if (value == NULL) {
        FLOG(stderr, "Failed to parse array\n");
        return JSN_ERROR;
    }
    if (value->arr_val == NULL) {
        FLOG(stderr, "Failed to parse array\n");
        return JSN_ERROR;
    }
    return JSN_SUCCESS;
}
