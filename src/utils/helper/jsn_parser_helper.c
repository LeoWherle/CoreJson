/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** jsn_parser_helper
*/

#include "corejson/internal.h"

static const char *json_value_type_string[] = {
    [JSON_STRING] = "JSON_STRING",
    [JSON_NUMBER] = "JSON_NUMBER",
    [JSON_TRUE] = "JSON_TRUE",
    [JSON_FALSE] = "JSON_FALSE",
    [JSON_BOOL] = "JSON_BOOL",
    [JSON_NULL] = "JSON_NULL",
    [JSON_OBJECT] = "JSON_OBJECT",
    [JSON_ARRAY] = "JSON_ARRAY",
};

const char *json_value_type_get_string(token_type_e type)
{
    return json_value_type_string[type];
}
