/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_parse_array
*/

#include <stdio.h>
#include "corejson_internal.h"

void jns_bool_print(
    json_value_t *value, UNUSED uint32_t depth, UNUSED bool format, int fd)
{
    dprintf(fd, "%s", value->bool_value ? TRUE_STR : FALSE_STR);
}
