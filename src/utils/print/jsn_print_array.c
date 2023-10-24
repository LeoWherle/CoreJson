/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_parse_array
*/

#include <stdio.h>
#include "corejson/internal.h"

void jsn_array_print(
    json_value_t *value, uint32_t depth, uint32_t format, int fd)
{
    json_array_t *array = value->array_value;

    if (value->array_value == NULL)
        return;
    dprintf(fd, "[");
    if (format) {
        dprintf(fd, "\n");
    }
    for (uint32_t i = 0; i < array->size; i++) {
        print_spaces(depth + 1, fd, format);
        jsn_value_print(&array->elements[i], depth + 1, format, fd);
        if (i < array->size - 1) {
            dprintf(fd, ",");
        }
        if (format) {
            dprintf(fd, "\n");
        }
    }
    print_spaces(depth, fd, format);
    dprintf(fd, "]");
}
