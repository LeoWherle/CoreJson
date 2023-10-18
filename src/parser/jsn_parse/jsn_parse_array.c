/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_parse_array
*/

#include "corejson_internal.h"

int jsn_tkn_parse_array(
    json_value_t *value, UNUSED token_t *token, const char **json)
{
    value->type = JSON_ARRAY;
    value = jsn_parse_array(json, value);
    if (value == NULL) {
        FLOG(stderr, "Failed to parse array\n");
        return 1;
    }
    if (value->array_value == NULL) {
        FLOG(stderr, "Failed to parse array\n");
        return 1;
    }
    return 0;
}
