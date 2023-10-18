/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_parse_array
*/

#include <stdio.h>
#include "corejson_internal.h"

void jsn_number_print(json_value_t *jsonValue, UNUSED uint32_t depth,
    UNUSED uint32_t format, int fd)
{
    if (jsonValue->number_value == (int) jsonValue->number_value) {
        dprintf(fd, "%d", (int) jsonValue->number_value);
        return;
    } else if (jsonValue->number_value == (long) jsonValue->number_value) {
        dprintf(fd, "%ld", (long) jsonValue->number_value);
        return;
    } else {
        dprintf(fd, "%f", jsonValue->number_value);
        return;
    }
}
