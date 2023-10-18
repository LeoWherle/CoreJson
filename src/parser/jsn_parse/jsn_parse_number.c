/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_parse_array
*/

#include <stdlib.h>
#include "corejson_internal.h"

int jsn_tkn_parse_number(
    json_value_t *value, token_t *token, UNUSED const char **json)
{
    value->type = JSON_NUMBER;
    value->number_value = atof(token->value);
    return 0;
}
