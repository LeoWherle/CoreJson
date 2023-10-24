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
    [JSON_ARRAY] = &jsn_array_print,
    [JSON_OBJECT] = &jsn_object_print,
    [JSON_NUMBER] = &jsn_number_print,
    [JSON_BOOL] = &jsn_bool_print,
    [JSON_STRING] = &jsn_string_print,
    [JSON_NULL] = &jsn_null_print,
};

void print_spaces(uint32_t depth, int fd, uint32_t format)
{
    uint32_t i = 0;
    uint32_t j = 0;

    for (i = 0; i < depth; i++) {
        for (j = 0; j < format; j++)
        dprintf(fd, "  ");
    }
}

void jsn_value_print(
    json_value_t *jsonValue, uint32_t depth, uint32_t format, int fd)
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

void jsn_print(json_value_t *jsonValue, uint32_t format, int fd)
{
    jsn_value_print(jsonValue, 0, format, fd);
}
