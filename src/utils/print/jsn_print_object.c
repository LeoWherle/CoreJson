/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_parse_array
*/

#include <stdio.h>
#include "corejson_internal.h"

void jsn_object_print(
    json_value_t *value, uint32_t depth, bool format, int fd)
{
    json_object_t *object = value->object_value;

    if (object == NULL)
        return;
    dprintf(fd, "{");
    if (format)
        dprintf(fd, "\n");
    for (uint32_t i = 0; i < object->size; i++) {
        print_spaces(depth + 1, fd, format);
        dprintf(fd, "\"%s\": ", object->keys[i]);
        jsn_value_print(&object->values[i], depth + 1, format, fd);
        if (i < object->size - 1) {
            dprintf(fd, ",");
        }
        if (format) {
            dprintf(fd, "\n");
        }
    }
    print_spaces(depth, fd, format);
    dprintf(fd, "}");
}
