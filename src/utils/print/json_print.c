/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_print
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "corejson_internal.h"

static const json_print_func_t json_print_funcs[] = {
    [JSON_ARRAY] = &jns_array_print,
    [JSON_OBJECT] = &jns_object_print,
    [JSON_NUMBER] = &jns_number_print,
    [JSON_FALSE] = &jns_bool_print,
    [JSON_TRUE] = &jns_bool_print,
    [JSON_STRING] = &jns_string_print,
    [JSON_NULL] = &jns_null_print,
};

void print_spaces(uint32_t depth, int fd, bool format)
{
    if (!format) {
        return;
    }
    for (uint32_t i = 0; i < depth; i++) {
        dprintf(fd, "  ");
    }
}

void json_print_value(
    json_value_t *jsonValue, uint32_t depth, bool format, int fd)
{
    if (jsonValue == NULL) {
        return;
    }
    if (IS_JSON_VALUE(jsonValue->type)) {
        json_print_funcs[jsonValue->type](jsonValue, depth, format, fd);
    } else {
        FLOG("Invalid json value type");
    }
}

void json_print(json_value_t *jsonValue, bool format, int fd)
{
    json_print_value(jsonValue, 0, format, fd);
}
